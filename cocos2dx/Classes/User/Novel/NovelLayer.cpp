#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

#include "../SceneManager.h"

#include "ScriptStaticData.h"

#include "../TouchiEvent/EventListenerGesture.h"

#include "../../Lib/Utilitys.h"

#include "../System/DataSettings.h"

#include "../../Lib/AudioManager.h"

USING_NS_CC;

namespace User
{
    cocos2d::Image* NovelLayer::screen = nullptr;

    NovelLayer::NovelLayer( std::string const& scenario, std::function<void( )> const& saveCallFunc )
        : textLabels( this )
        , novelPath( scenario )
        , saveCallFunc( saveCallFunc )
        , readProceed( false )
        , systemRead( true )
        , systemStop( false )
    {

    }
    NovelLayer::~NovelLayer( )
    {
        AudioManager::getInstance( )->stopAllSe( );
        AudioManager::getInstance( )->stopAllBgm( );
        AudioManager::getInstance( )->stopAllVoice( );
    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        next_scene = [ ] {SceneManager::createCityMap( ); };

        this->scheduleUpdate( );

        auto touch = EventListenerTouchOneByOne::create( );
        touch->onTouchBegan = [ this ] ( Touch* touch, Event* event )
        {
            tap_began = true;

            return true;
        };
        touch->onTouchEnded = [ this ] ( Touch* touch, Event* event )
        {
            if ( automode )
            {
                removeChild( automode );
                automode = nullptr;
            }
            click( );

            readProceed.off( );

            tap_began = false;
            long_tap_began = false;
            tap_time = 0.0F;
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touch, this );

        return true;
    }
    void NovelLayer::setup( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        Sprite* window = Sprite::create( u8"res/texture/system/message.window.png" );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        window->setAnchorPoint( Vec2( 0, 0 ) );
        auto boardPixel = window->getContentSize( ) / scale;
        auto boardScale = Lib::fitWidth( window, vs.width );
        window->setScale( boardScale, boardScale );
        this->addChild( window );
        novelWindow = window;

        textLabels.animationEndCallBack = [ this ]
        {
            // ここでスクショを撮る
            delete screen;
            screen = utils::captureNode( Director::getInstance( )->getRunningScene( ) );

            auto visibleSize = Director::getInstance( )->getVisibleSize( );
            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
            auto size = novelWindow->getContentSize( );
            auto mul = size.width / visibleSize.width;
            auto position = Vec2( 950.0F * scale, ( 400.0F - 340.0F ) * scale );
            auto icon = NovelReadedPointer::create( )->make( );
            icon->setPosition( position );
            novelWindow->addChild( icon );

            if ( automode )
            {
                if ( !systemStop ) automode->restart( );
            }
        };
        textChunkManager.readEndCallBack = [ this ]
        {
            // テキストデータを貼り付けて。
            textPasting( );
            // システム読み込みを停止。
            systemRead.off( );
        };
        textChunkManager.novelEndCallBack = [ this ]
        {
            systemStop.on( );
            systemRead.off( );
            textChunkManager.novelEndCallBack = nullptr;

            if ( auto sprite = Sprite::create( ) )
            {
                sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                sprite->setAnchorPoint( Vec2( 0, 0 ) );
                sprite->setColor( Color3B( 0, 0, 0 ) );
                sprite->setOpacity( 0 );
                sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this ]
                {
                    // ここで、オートセーブデータを書き込みます。
                    if ( saveCallFunc )saveCallFunc( );

                    if ( !UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) )
                    {
                        Lib::next_day( );
                    }

                    // 絶対関数の中に次のシーンを入れます。
                    next_scene( );
                } ), RemoveSelf::create( ), nullptr ) );
                Director::getInstance( )->getRunningScene( )->addChild( sprite );
            }
        };

        textChunkManager.make( novelPath );
    }
    void NovelLayer::update( float delta )
    {
        // ロングタップ
        if ( ( tap_began ) && ( !long_tap_began ) && ( 0.3F < ( tap_time += delta ) ) )
        {
            readProceed.on( );
            long_tap_began = true;
        }

        textChunkManager.updateDelay( delta );

        // 高速読み込みのアップデート
        // キーボードの左側のCTRLを押している間だけ高速読み込み機能がONになります。
        readingProceedUpdate( );

        // テキストの読み込み。
        // delayが0である限り、テキストを読み込み続けます。
        readNextNovel( );
    }
    void NovelLayer::on( )
    {
        enumerateChildren( "//.*", [ ] ( cocos2d::Node* node )
        {
            node->runAction( FadeIn::create( 0.3F ) );
            return false;
        } );
    }
    void NovelLayer::off( )
    {
        enumerateChildren( "//.*", [ ] ( cocos2d::Node* node )
        {
            node->runAction( FadeOut::create( 0.3F ) );
            return false;
        } );
    }
    void NovelLayer::novelenable( )
    {
        this->resume( );
        this->setVisible( true );
    }
    void NovelLayer::noveldisable( )
    {
        this->pause( );
        this->setVisible( false );
    }
    void NovelLayer::stop( )
    {
        readProceed.off( );

        tap_began = false;
        long_tap_began = false;
        tap_time = 0.0F;

        pause( );
    }
    void NovelLayer::restart( )
    {
        resume( );
    }
    void NovelLayer::skip( )
    {
        while ( !systemStop || !textChunkManager.isNovelFinished( ) )
        {
            if ( textLabels.getIsReadOuted( ) )
            {
                novelWindow->removeChildByName( u8"novelReadedAnimation" );
                // テキストの中身を消します。
                textClear( );
            }
            else
            {
                auto action = Director::getInstance( )->getActionManager( );
                action->update( 10.0F );
                textActionStop( );
            }
            textChunkManager.textRead( );
        }
    }
    void NovelLayer::addAuto( )
    {
        if ( automode )
        {
            removeChild( automode );
            automode = nullptr;
        }

        // すでに停止状態
        if ( textLabels.getIsReadOuted( ) )
        {
            // すぐに、次のアニメーションに映る。
            click( );
            automode = AutoMode::create( [ this ] { click( ); } );
            addChild( automode );
            automode->stop( );
        }
        else
        {
            automode = AutoMode::create( [ this ] { click( ); } );
            addChild( automode );
        }
    }
    void NovelLayer::select( std::string const & name )
    {
        systemStop.off( );
        restart( );

        auto selectLayer = this->getLayer<SelectLayer>( );

        // 選択肢のレイヤーを削除
        if ( auto ptr = dynamic_cast<Menu*>( selectLayer->getChildByName( u8"select" ) ) )
        {
            ptr->setEnabled( false );
            ptr->runAction( Sequence::create( FadeOut::create( 0.3 ), RemoveSelf::create( ), nullptr ) );
        }

        // 次に読み込むシナリオデータを指定。
        textChunkManager.select( name );
    }
    void NovelLayer::textClear( )
    {
        textChunkManager.gotoNext( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // テキストデータを読み込み終わったらラベルに貼り付ける。
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto size = Sprite::create( u8"res/texture/system/message.window.png" )->getContentSize( );
        auto mul = size.width / visibleSize.width;
        textLabels.setStrings( textChunkManager.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     297 / mul / scale ) );
    }
    void NovelLayer::readingProceedUpdate( )
    {
        // 高速読み込みが可能なら文字を1フレームに1回読み続ける。
        if ( readProceed )
        {
            // 高速読み込みではdelayは無視します。
            textChunkManager.setDelayTime( 0.0F );
            click( );
        }
    }
    void NovelLayer::click( )
    {
        if ( systemStop ) return;

        if ( automode )
        {
            automode->stop( );
        }

        if ( textLabels.getIsReadOuted( ) )
        {
            novelWindow->removeChildByName( u8"novelReadedAnimation" );
            makeLoadingFeatureOn( );
        }
        else
        {
            auto action = Director::getInstance( )->getActionManager( );
            action->update( 10.0F );
            textActionStop( );
        }
    }
    void NovelLayer::next( )
    {
        if ( systemStop ) return;

        if ( automode )
        {
            automode->stop( );
        }

        textActionStop( );
        novelWindow->removeChildByName( u8"novelReadedAnimation" );
        makeLoadingFeatureOn( );
    }
    //　テキストのアニメーションが終わっている場合
    void NovelLayer::makeLoadingFeatureOn( )
    {
        // 新しくテキストを読み込んで良い場合。
        if ( !systemStop )
        {
            // テキストの中身を消します。
            textClear( );
            // 読み込みを開始の合図を出します。
            systemRead.on( );
        }
    }
    void NovelLayer::readNextNovel( )
    {
        if ( systemRead )
        {
            textChunkManager.textRead( );
        }
    }
    // テキストのアニメーションが終わっていない場合
    void NovelLayer::textActionStop( )
    {
        textChunkManager.setDelayTime( 0.0F );
        readNextNovel( );

        textLabels.actionStop( );
    }
    NovelReadedPointer* NovelReadedPointer::make( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto path = u8"res/texture/system/crystal.png";
        auto sprite = Sprite::create( path );
        auto size = sprite->getContentSize( );
        const int sx = 6;
        const int sy = 5;
        const auto parts = Size( size.width / sx, size.height / sy );
        setContentSize( parts * scale );
        Vector<SpriteFrame*> frames;
        for ( int y = 0; y < sy; ++y )
        {
            for ( int x = 0; x < sx; ++x )
            {
                auto rect = Rect( x * parts.width, y * parts.height, parts.width, parts.height );
                frames.pushBack( SpriteFrame::create( path, rect ) );
            }
        }
        auto animation = Animation::createWithSpriteFrames( frames, 0.016F );
        setScale( Lib::fitHeight( this, 64 * scale ), Lib::fitHeight( this, 64 * scale ) );
        runAction( RepeatForever::create( Animate::create( animation ) ) );
        setName( u8"novelReadedAnimation" );
        setAnchorPoint( Vec2( 1, 0 ) );

        return this;
    }
    AutoMode * AutoMode::create( std::function<void( )> const & tick )
    {
        AutoMode *pRet = new( std::nothrow ) AutoMode( );
        if ( pRet && pRet->init( tick ) )
        {
            pRet->autorelease( );
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    bool AutoMode::init( std::function<void( )> const & tick )
    {
        if ( !Node::init( ) ) return false;
        this->tick = tick;
        setName( typeid( this ).name( ) );
        stop( );
        scheduleUpdate( );
        return true;
    }
    void AutoMode::update( float t )
    {
        if ( 3.0F < ( timer += t ) )
        {
            if ( tick )tick( );
            timer = 0.0F;
        }
    }
    void AutoMode::stop( )
    {
        pause( );
    }
    void AutoMode::restart( )
    {
        resume( );
        timer = 0.0F;
    }
}
