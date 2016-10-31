#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( )
        : textLabels( this )
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
                textData.makeData( "scenario1.txt" );
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

        auto mouseEvent = EventListenerMouse::create( );
        mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        {
            if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
            {
                //　テキストのアニメーションが終わっている場合
                if ( textLabels.getIsReadOuted( ) )
                {
                    // テキストの中身を消します。
                    textClear( );
                    // 読み込みを開始します。
                    switchIsSystemRead( );
                }
                // テキストのアニメーションが終わっていない場合
                else
                {
                    // テキストの中身を消します。
                    textClear( );

                    while ( delayTime == 0.0 )
                    {
                        // テキストを読み始めます。
                        textPartyUpdate( );

                        // 読み込み終了なら
                        if ( textChank.isReadFinished( ) )
                        {
                            // テキストデータを貼り付けて。
                            textPasting( );
                            // システム読み込みを停止。
                            switchIsSystemRead( );

                            break;
                        }

                        // ディレイは完全に無視します。
                        delayTime = 0.0;
                    }
                }
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

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

        textData.makeData( "scenario1.txt" );
        textUpdate( 0.0F );
    }
    void NovelLayer::update( float delta )
    {
        // 高速読み込みが可能なら文字を1フレームに1回読み続ける。
        if ( isReadingProceed )
        {
            textUpdate( delta );
        }

        // 読み込み
        if ( isSystemRead )
        {
            textUpdate( delta );
        }
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );

        // 選択肢のレイヤーを削除
        selectLayer->removeAllChildren( );

        // 次に読み込むシナリオデータを指定。
        textData.setNextChild( name );

        switchIsSelectStopping( );
    }
    void NovelLayer::textUpdate( float delta )
    {
        while ( delayTime == 0.0 )
        {
            // テキストを読み始めます。
            textPartyUpdate( );

            // 読み込み終了なら
            if ( textChank.isReadFinished( ) )
            {
                // テキストデータを貼り付けて。
                textPasting( );
                // システム読み込みを停止。
                switchIsSystemRead( );

                break;
            }

            delayTime = std::max( delayTime - delta, 0.0 );
        }
    }
    void NovelLayer::textPartyUpdate( )
    {
        if ( !textChank.isReadFinished( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
        }
    }
    void NovelLayer::textClear( )
    {
        // 読み込みを無効にしているなら早期リターンします。
        if ( !isSelectStopping ) return;

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
}
