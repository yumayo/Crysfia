#include "UIManager.h"
#include "Test.h"
#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    UIManager::UIManager( ) :
        menuWindow( nullptr ),
        swicthWindow( nullptr ),
        optionIcon( nullptr ),
        isOpen( false )
    {
    }

    UIManager::~UIManager( ) {}

    bool UIManager::init( )
    {
        if ( !Layer::init( ) ) { return false; }

        auto winSize = Director::getInstance( )->getWinSize( );
        auto size = Size( 720, 1280 );

        createMenuWindow( );
        createOptionIcon( );
        //this->scheduleUpdate();	update()関数を使うときはコメントアウトを外す
        return true;
    }

    void UIManager::createMenuWindow( )
    {
        Size size = Size( 720, 1280 );

        Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
        Vec2 winSize = Director::getInstance( )->getWinSize( );

        auto layout = ui::Layout::create( );
        layout->setPosition( Vec2( 620, 10 ) );
        layout->setContentSize( Size( size.width, 150 ) );
        auto layoutSize = layout->getContentSize( );

    #if _DEBUG //デバッグ時、layoutを黒くする
        auto bg = LayerColor::create( Color4B::BLACK, layoutSize.width, layoutSize.height );
        bg->setOpacity( 128 );
        layout->addChild( bg );
    #endif //_DEBUG

            //メニューの背景
        auto menuImage = ui::Scale9Sprite::create( "res/Image/WindowBase/WinBase_88.png",
                                                   Rect( 0 / CC_CONTENT_SCALE_FACTOR( ), 0 / CC_CONTENT_SCALE_FACTOR( ),
                                                         120 / CC_CONTENT_SCALE_FACTOR( ), 120 / CC_CONTENT_SCALE_FACTOR( ) ),
                                                   Rect( 32 / CC_CONTENT_SCALE_FACTOR( ), 32 / CC_CONTENT_SCALE_FACTOR( ),
                                                         64 / CC_CONTENT_SCALE_FACTOR( ), 64 / CC_CONTENT_SCALE_FACTOR( ) ) );
        menuImage->setPosition( layoutSize / 2 );
        menuImage->setContentSize( layout->getContentSize( ) );
        layout->addChild( menuImage );

        //メニューウィンドウの開閉用ボタン
        swicthWindow = ui::Button::create( "res/Image/WindowBase/WinBase_1.png" );
        swicthWindow->setScaleX( 0.25f );
        swicthWindow->setScaleY( 0.5f );
        swicthWindow->setPosition( Vec2( 60, layoutSize.height / 2 ) );
        layout->addChild( swicthWindow );


        for ( int i = 0; i < MenuType::MAX; i++ )
        {
            menuButtons.push_back( ui::Button::create( "res/Image/WindowBase/WinBase_24.png" ) );
            menuButtons[i]->setScale( 0.5 );
            menuButtons[i]->setPosition( Vec2( 120 * ( i + 1.3f ), layoutSize.height / 2 ) );
            layout->addChild( menuButtons[i] );

        }
        // 先頭ボタンを押すと、次のシーンに飛びます。
        menuButtons.front( )->addTouchEventListener( [ & ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                SceneManager::createIslandMap( );
            }
        } );

        this->addChild( layout, 0, Menu );

        /**************************************
                    各ボタンUIの処理
        ***************************************/

        //メニュー開閉用ボタン
        swicthWindow->addTouchEventListener( [ & ] ( Ref *pSender, ui::Widget::TouchEventType type ) {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                auto m = getChildByTag( Menu );
                isOpen = !isOpen;
                if ( !isOpen ) {
                    auto action = MoveBy::create( 0.2f, Vec2( 620, 0 ) );
                    m->runAction( action );
                }
                else if ( isOpen ) {
                    auto action = MoveBy::create( 0.2f, Vec2( -620, 0 ) );
                    m->runAction( action );
                }
            }
        } );

        /* ---TODO---
            残りの各ボタンの処理を書く。終わったら下のリストを消す
            ストーリー、
            食事、
            着替え、
            掃除、
            日記
        */

        //オプションウィンドウ
        auto button = ui::Button::create( "res/Image/option_icon.png" );
        button->setScale( 0.5f );
        button->setPosition( Vec2( 50, -50 ) );
        layout->addChild( button );

    }

    //オプションウィンドウの生成
    void UIManager::setOptionWindow( )
    {
        Size winSize = Size( 800, 1280 );
        Size contentWinSize = Size( 500, 600 );

        auto list = ui::ListView::create( );
        list->setContentSize( winSize );
        this->addChild( list, 0, Option );

        auto layout = ui::Layout::create( );
        layout->setContentSize( winSize );
        list->addChild( layout );

        auto layoutSize = layout->getContentSize( );

    #if _DEBUG
        auto bg = LayerColor::create( Color4B::WHITE, layout->getContentSize( ).width, layout->getContentSize( ).height );
        bg->setOpacity( 128 );
        layout->addChild( bg );
    #endif //_DEBUG

        auto menuImage = ui::Scale9Sprite::create( "res/Image/WindowBase/WinBase_59.png",
                                                   Rect( 0 / CC_CONTENT_SCALE_FACTOR( ), 0 / CC_CONTENT_SCALE_FACTOR( ),
                                                         120 / CC_CONTENT_SCALE_FACTOR( ), 120 / CC_CONTENT_SCALE_FACTOR( ) ),
                                                   Rect( 32 / CC_CONTENT_SCALE_FACTOR( ), 32 / CC_CONTENT_SCALE_FACTOR( ),
                                                         64 / CC_CONTENT_SCALE_FACTOR( ), 64 / CC_CONTENT_SCALE_FACTOR( ) ) );

                                                 //オプションウィンドウの位置。修正した値
        auto winPos = Vec2( list->getContentSize( ).width / 2 - 40, list->getContentSize( ).height / 2 );
        menuImage->setPosition( winPos );
        menuImage->setContentSize( contentWinSize );
        layout->addChild( menuImage );

        //CloseButton（仮置き）
        auto closeButton = ui::Button::create( "res/Image/WindowBase/WinBase_18.png" );
        closeButton->setTitleFontSize( 60 );
        closeButton->setTitleText( "CLOSE" );
        closeButton->setScaleX( 0.6f );
        closeButton->setScaleY( 0.5f );
        closeButton->setPosition( Vec2( winPos.x, winPos.y - 200 ) );
        layout->addChild( closeButton );

        //CloseButtonの処理
        //ボタンを押したときにLayerに追加されているOptionタグを持つ子ノードを取得しLayerから外している
        closeButton->addTouchEventListener( [ & ] ( Ref* pSender, ui::Widget::TouchEventType type ) {
            auto option = this->getChildByTag( Option );
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                this->removeChild( option );
            }
        } );
    }

    //TIPS: UIのListViewやLayoutの原点位置はSpriteなど中央ではなく左下になっている

    void UIManager::createOptionIcon( )
    {
        Size winSize = Size( 800, 1280 );

        auto iconSize = Size( 100, 100 );
        auto layout = ui::Layout::create( );
        layout->setPosition( Vec2( 25, 1150 ) );
        layout->setContentSize( iconSize );
        this->addChild( layout );

        auto optionButton = ui::Button::create( "res/Image/option_icon.png" );
        optionButton->setPosition( layout->getContentSize( ) / 2 );
        optionButton->setScale( 0.5 );
        layout->addChild( optionButton );
        int a = 0;
        optionButton->addTouchEventListener( [ & ] ( Ref* pSender, ui::Widget::TouchEventType type ) {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                setOptionWindow( );
            }
        } );
    }

    void UIManager::update( float dt )
    {
    }

}
