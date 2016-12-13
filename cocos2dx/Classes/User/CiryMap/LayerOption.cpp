#include "LayerOption.h"


#include "../../Lib/Utility/Utilitys.h"

#include "ui/CocosGUI.h"

#include "../Novel/OptionalValues.h"

USING_NS_CC;

namespace User
{
    LayerOption::LayerOption( )
    {

    }
    LayerOption::~LayerOption( )
    {

    }
    bool LayerOption::init( )
    {
        if ( !Layer::init( ) ) return false;

        std::string dir = u8"res/texture/system/";
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        // 簡易的なモーダルレイヤーです。
        // 透明な画像を画面いっぱいに貼ることで機能しています。
        {
            auto modal = ui::Button::create( dir + u8"null.png" );

            modal->setScale( vs.width * 0.5 * scale, vs.height * 0.5 * scale );
            modal->setPosition( vo + vs * 0.5 );
            addChild( modal );
        }


        {
            auto background = Sprite::create( dir + u8"slider.background.png" );
            addChild( background );
            background->setScale( Lib::fitWidth( background, vs.width ) );
            background->setPosition( vo + vs * 0.5 );
            auto pixel = background->getContentSize( );

            auto listView = ui::ListView::create( );
            background->addChild( listView );
            listView->setContentSize( Size( 1080, 600 ) / scale );
            listView->setAnchorPoint( Vec2( 0.5, 0.5 ) );
            listView->setPosition( pixel * 0.5F );

            {
                auto bar = SlideBar::create( u8"bgm" );
                auto layout = ui::Layout::create( );
                listView->addChild( layout );
                layout->setContentSize( Size( bar->getContentSize( ).width, bar->getContentSize( ).height * 2 ) );
                layout->addChild( bar );

                // スライダーラベルを生成
                auto label = Label::createWithTTF( u8"BGM", u8"res/fonts/HGRGE.TTC", 64 );
                // ラベルの色
                label->setColor( Color3B::WHITE );
                // ラベルの設置
                label->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
                // ラベルタイトルを追加
                layout->addChild( label );
                label->setAnchorPoint( Vec2( 0, 0 ) );
            }

            {
                auto bar = SlideBar::create( u8"se" );
                auto layout = ui::Layout::create( );
                listView->addChild( layout );
                layout->setContentSize( Size( bar->getContentSize( ).width, bar->getContentSize( ).height * 2 ) );
                layout->addChild( bar );

                // スライダーラベルを生成
                auto label = Label::createWithTTF( u8"SE", u8"res/fonts/HGRGE.TTC", 64 );
                // ラベルの色
                label->setColor( Color3B::WHITE );
                // ラベルの設置
                label->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
                // ラベルタイトルを追加
                layout->addChild( label );
                label->setAnchorPoint( Vec2( 0, 0 ) );
            }

            {
                auto bar = SlideBar::create( u8"novel.speed" );
                bar->slider->setMaxPercent( 30 );

                auto layout = ui::Layout::create( );
                listView->addChild( layout );
                layout->setContentSize( Size( bar->getContentSize( ).width, bar->getContentSize( ).height * 2 ) );
                layout->addChild( bar );

                // スライダーラベルを生成
                auto label = Label::createWithTTF( u8"ノベルの読み上げ速度", u8"res/fonts/HGRGE.TTC", 64 );
                // ラベルの色
                label->setColor( Color3B::WHITE );
                // ラベルの設置
                label->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
                // ラベルタイトルを追加
                layout->addChild( label );
                label->setAnchorPoint( Vec2( 0, 0 ) );

                auto barsize = bar->getContentSize( );
                listView->setContentSize( Size( barsize.width, barsize.height * 2 * 5 ) );

                /**
                *  画面下部のメニュー
                */
                auto board = Sprite::create( u8"res/texture/system/board.png" );
                auto boardPixel = board->getContentSize( ) / scale;
                auto boardScale = Lib::fitWidth( board, vs.width );
                {
                    board->setScale( boardScale, boardScale );
                    board->setAnchorPoint( Vec2( 0, 0 ) );
                    board->setPosition( vo );
                    addChild( board );

                    auto height = boardPixel.height - 10 * 2;
                    if ( auto button = createBackButton( ) )
                    {
                        board->addChild( button );
                        button->setScale( Lib::fitHeight( button, height * scale ), Lib::fitHeight( button, height * scale ) );
                        button->setPosition( Vec2( 10, 10 ) * scale );
                    }
                }


                auto message = Sprite::create( u8"res/texture/system/message.window.png" );
                auto messagePixel = message->getContentSize( ) / scale;
                auto messageScale = Lib::fitWidth( message, vs.width );
                {
                    message->setScale( messageScale, messageScale );
                    message->setAnchorPoint( Vec2( 0, 0 ) );
                    message->setPosition( vo + Vec2( 0, 200 * boardScale / scale ) );
                    addChild( message );
                }


                auto test = Label::createWithTTF( u8"読み上げのテスト、速度はこんな感じです。", OptionalValues::fontName, OptionalValues::fontSize / messageScale );
                test->setTextColor( Color4B( 39, 39, 39, 255 ) );
                {
                    test->setPosition( messagePixel.width * 0.5 * scale, messagePixel.height * 0.5 * scale );
                    test->setAnchorPoint( Vec2( 0.5, 0 ) );
                    for ( int i = 0, size = test->getStringLength( ); i < size; ++i )
                    {
                        auto oneString = test->getLetter( i );
                        if ( oneString )
                        {
                            oneString->setOpacity( 0 );
                            auto seq = Sequence::create( DelayTime::create( OptionalValues::readOutSpeed * i ),
                                                         FadeIn::create( OptionalValues::readOutSpeed ),
                                                         DelayTime::create( OptionalValues::readOutSpeed * ( size - i ) ),
                                                         CallFunc::create( [ = ] { oneString->setOpacity( 0 ); } ),
                                                         nullptr );
                            oneString->runAction( RepeatForever::create( seq ) );
                        }
                    }
                }
                message->addChild( test );

                bar->move = [ = ] ( float t )
                {
                    OptionalValues::readOutSpeed = t;
                    for ( int i = 0, size = test->getStringLength( ); i < size; ++i )
                    {
                        auto oneString = test->getLetter( i );
                        if ( oneString )
                        {
                            oneString->stopAllActions( );
                            oneString->setOpacity( 0 );
                            auto seq = Sequence::create( DelayTime::create( OptionalValues::readOutSpeed * i ),
                                                         FadeIn::create( OptionalValues::readOutSpeed ),
                                                         DelayTime::create( OptionalValues::readOutSpeed * ( size - i ) ),
                                                         CallFunc::create( [ = ] { oneString->setOpacity( 0 ); } ),
                                                         nullptr );
                            oneString->runAction( RepeatForever::create( seq ) );
                        }
                    }
                };
            }
        }

        return true;
    }
    void LayerOption::setup( )
    {

    }
    cocos2d::ui::Button * LayerOption::createBackButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 0, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                removeFromParentAndCleanup( true );
            }
        } );
        return button;
    }
    SlideBar::SlideBar( )
    {
        std::string dir = u8"res/texture/system/";
        slider = ui::Slider::create( );
        addChild( slider );

        auto scale = Director::getInstance( )->getContentScaleFactor( );

        slider->loadBarTexture( dir + u8"slider.process.base.png" );
        slider->loadProgressBarTexture( dir + u8"slider.process.bar.png" );
        slider->loadSlidBallTextures( dir + u8"slider.button.base.png", dir + u8"slider.button.selected.png" );
        slider->addEventListener( [ this ] ( Ref* ref, ui::Slider::EventType type )
        {
            ui::Slider* slider = dynamic_cast<ui::Slider*>( ref );
            auto percent = slider->getPercent( ) / 100.0F;
            if ( move ) move( percent );
            if ( type == ui::Slider::EventType::ON_SLIDEBALL_UP )
            {
                if ( ended ) ended( percent );
                if ( !key.empty( ) ) UserDefault::getInstance( )->setFloatForKey( key.c_str( ), percent );
            }
        } );
        slider->setAnchorPoint( Vec2( -128.0F / 2 / 800, 0 ) );
        setContentSize( slider->getContentSize( ) + Size( 128 * 2, 128 ) * scale );
    }
    SlideBar::SlideBar( float t )
        : SlideBar( )
    {
        slider->setPercent( t * 100 );
    }
    SlideBar::SlideBar( std::string key )
        : SlideBar( )
    {
        this->key = key;

        auto value = UserDefault::getInstance( )->getFloatForKey( key.c_str( ) );
        slider->setPercent( value * 100.0F );
    }
}
