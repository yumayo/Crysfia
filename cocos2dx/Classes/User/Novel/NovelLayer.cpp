#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

#include "../SceneManager.h"

#include "ScriptStaticData.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( std::string const & novelPath )
        : textLabels( this )
        , novelPath( novelPath )
        , readProceed( false )
        , systemRead( true )
        , systemStop( false )
    {
    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                //textData.makeData( novelPath );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // 左側のCTRLキーが押されたら高速読み込みを開始する。
                readProceed.on( );
            }
        };
        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // 左側のCTRLが離されたら高速読み込みを停止する。
                readProceed.off( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto multiTouchEvent = EventListenerTouchAllAtOnce::create( );
        multiTouchEvent->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                click( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( multiTouchEvent, this );

        //auto mouseEvent = EventListenerMouse::create( );
        //mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        //{
        //    if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
        //    {
        //        textUpdate( );
        //    }
        //};
        //this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

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
            auto visibleSize = Director::getInstance( )->getVisibleSize( );
            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
            auto size = novelWindow->getContentSize( );
            auto mul = size.width / visibleSize.width;
            auto position = Vec2( 950.0F * scale, ( 400.0F - 340.0F ) * scale );
            auto icon = NovelReadedPointer::create( )->make( );
            icon->setPosition( position );
            novelWindow->addChild( icon );
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
            systemRead.off( );

            if ( auto sprite = Sprite::create( ) )
            {
                sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                sprite->setAnchorPoint( Vec2( 0, 0 ) );
                sprite->setColor( Color3B( 0, 0, 0 ) );
                sprite->setOpacity( 0 );
                sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ ]
                {
                    auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
                    UserDefault::getInstance( )->setIntegerForKey( u8"日", day + 1 );
                    SceneManager::createIslandMap( );
                } ), RemoveSelf::create( ), nullptr ) );
                Director::getInstance( )->getRunningScene( )->addChild( sprite, 20000 );
            }
        };

        textChunkManager.make( novelPath );
    }
    void NovelLayer::update( float delta )
    {
        textChunkManager.updateDelay( delta );

        // 高速読み込みのアップデート
        // キーボードの左側のCTRLを押している間だけ高速読み込み機能がONになります。
        readingProceedUpdate( );

        // テキストの読み込み。
        // delayが0である限り、テキストを読み込み続けます。
        readNextNovel( );
    }
    void NovelLayer::delayOn( )
    {
        this->scheduleOnce( [ this ] ( float delay )
        {
            this->resume( );
        }, 0.016F, std::string( "novel.layer.delay" ) );

        this->setVisible( true );
    }
    void NovelLayer::on( )
    {
        this->resume( );
        this->setVisible( true );
    }
    void NovelLayer::off( )
    {
        this->pause( );
        this->setVisible( false );
    }
    void NovelLayer::select( std::string const & name )
    {
        systemStop.off( );

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
        textLabels.setStrings( textChunkManager.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     311 * scale - OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
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
        if ( textLabels.getIsReadOuted( ) )
        {
            novelWindow->removeChildByName( u8"novelReadedAnimation" );
            makeLoadingFeatureOn( );
        }
        else
        {
            textActionStop( );
        }
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
}
