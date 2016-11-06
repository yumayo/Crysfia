#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( std::string const & novelPath )
        : textLabels( this )
        , novelPath( novelPath )
    {
    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                textData.makeData( novelPath );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // 左側のCTRLキーが押されたら高速読み込みを開始する。
                switchIsReadingProceed( );
            }
        };

        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // 左側のCTRLが話されたら高速読み込みを停止する。
                switchIsReadingProceed( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto multiTouchEvent = EventListenerTouchAllAtOnce::create( );
        multiTouchEvent->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                textUpdate( );
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
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( origin.x, origin.y, visibleSize.width, OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        square->setPosition( rect.origin + rect.size / 2 );
        this->addChild( square );

        textData.makeData( novelPath );
        textRead( );
    }
    void NovelLayer::update( float delta )
    {
        delayTime = std::max( delayTime - delta, 0.0 );

        // 高速読み込みのアップデート
        // キーボードの左側のCTRLを押している間だけ高速読み込み機能がONになります。
        readingProceedUpdate( );

        // テキストの読み込み。
        // delayが0である限り、テキストを読み込み続けます。
        if ( isSystemRead ) textRead( );
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );

        // 選択肢のレイヤーを削除
        selectLayer->removeAllChildren( );

        // 次に読み込むシナリオデータを指定。
        textData.setNextChild( name );

        switchIsStopping( );
    }
    void NovelLayer::textRead( )
    {
        while ( delayTime == 0.0 )
        {
            // テキストを読み始めます。
            textPartyRead( );

            // 読み込み終了なら
            if ( textChank.isReadFinished( ) )
            {
                // テキストデータを貼り付けて。
                textPasting( );
                // システム読み込みを停止。
                switchIsSystemRead( );

                break;
            }
        }
    }
    void NovelLayer::textPartyRead( )
    {
        if ( !textChank.isReadFinished( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
        }
    }
    void NovelLayer::textClear( )
    {
        textChank.clear( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // テキストデータを読み込み終わったらラベルに貼り付ける。
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChank.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
    void NovelLayer::readingProceedUpdate( )
    {
        // 高速読み込みが可能なら文字を1フレームに1回読み続ける。
        if ( isReadingProceed )
        {
            // 高速読み込みではdelayは無視します。
            delayTime = 0.0F;
            textUpdate( );
        }
    }
    void NovelLayer::textUpdate( )
    {
        if ( textLabels.getIsReadOuted( ) )
        {
            textNextRead( );
        }
        else
        {
            textActionStop( );
        }
    }
    //　テキストのアニメーションが終わっている場合
    void NovelLayer::textNextRead( )
    {
        // 新しくテキストを読み込んで良い場合。
        if ( !isStopping )
        {
            // テキストの中身を消します。
            textClear( );
            // 読み込みを開始します。
            switchIsSystemRead( );
        }
    }
    // テキストのアニメーションが終わっていない場合
    void NovelLayer::textActionStop( )
    {
        if ( isSystemRead )
        {
            textRead( );
        }

        textLabels.actionStop( );
    }
}
