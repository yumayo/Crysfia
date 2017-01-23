#include "LayerOption.h"

#include "../../Lib/Utilitys.h"

#include "ui/CocosGUI.h"

#include "../Novel/OptionalValues.h"

#include "../SceneManager.h"

#include "LayerCity.h"

#include "../../Lib/AudioManager.h"

#include "../LayerSave/LayerSave.h"

#include "../System/DataSettings.h"


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

        scheduleUpdate( );

        std::string dir = u8"res/texture/system/";
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        addChild( createModal( ) );

        auto background = Sprite::create( dir + u8"slider.background.png" );
        addChild( background );
        background->setScale( Lib::fitWidth( background, vs.width ) );
        background->setPosition( vo + vs * 0.5 );

        /**
        *  画面下部のメニュー
        */
        auto board = Sprite::create( u8"res/texture/system/board.png" );
        {
            auto boardPixel = board->getContentSize( ) / scale;
            board->setScale( Lib::fitWidth( board, vs.width ) );
            board->setAnchorPoint( Vec2( 0, 0 ) );
            board->setPosition( vo );
            addChild( board );

            auto height = boardPixel.height - 10 * 2;

            auto back_button = createBackButton( );
            if ( back_button )
            {
                board->addChild( back_button );
                back_button->setScale( Lib::fitHeight( back_button, height * scale ) );
                back_button->setPosition( Vec2( 10, 10 ) * scale );
            }
            auto delete_button = createDeleteButton( );
            if ( delete_button )
            {
                board->addChild( delete_button );
                delete_button->setScale( Lib::fitHeight( delete_button, height * scale ) );
                delete_button->setPosition( Vec2( boardPixel.width - 10, 10 ) * scale );
            }
            auto savemenu_button = createSaveMenuButton( );
            if ( savemenu_button )
            {
                board->addChild( savemenu_button );
                savemenu_button->setScale( Lib::fitHeight( savemenu_button, height * scale ) );
                savemenu_button->setPosition( Vec2( boardPixel.width - 10 -
                                                    delete_button->getContentSize( ).width * delete_button->getScale( ) - 10, 10 ) * scale );
            }
        }

        //画面下部に表示されるメッセージウィンドウのサイズ
        auto message = Sprite::create( u8"res/texture/system/message.window.png" );
        message->setScale( Lib::fitWidth( message, vs.width ) );

        auto listView = ui::ListView::create( );
        addChild( listView );
        listView->setContentSize( Size( vs.width,
                                        vs.height
                                        - board->getContentSize( ).height * board->getScale( )
                                        - message->getContentSize( ).height * message->getScale( ) ) );
        listView->setAnchorPoint( Vec2( 0, 1 ) );
        listView->setPosition( vo + Vec2( 0, vs.height ) );

        /**
         * BGM
         */
        {
            auto layout = ui::Layout::create( );

            auto bar = SlideBar::create( u8"bgm" );
            bar->move = [ ] ( float t )
            {
                auto audio = AudioManager::getInstance( );
                audio->setBgmVolume( t );
            };
            auto logo = Sprite::create( u8"res/texture/system/logo.bgm.png" );
            layout->setContentSize( Size( bar->getContentSize( ).width,
                                          bar->getContentSize( ).height + logo->getContentSize( ).height ) );
            listView->addChild( layout );
            layout->setScale( Lib::fitWidth( layout, listView->getContentSize( ).width ) );
            layout->setContentSize( layout->getContentSize( ) * layout->getScale( ) );
            layout->addChild( bar );
            layout->addChild( logo );

            bar->setAnchorPoint( Vec2( 0, 0 ) );
            logo->setAnchorPoint( Vec2( 0, 0 ) );

            logo->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
        }

        /**
         * SE
         */
        {
            auto layout = ui::Layout::create( );

            auto bar = SlideBar::create( u8"se" );
            bar->move = [ ] ( float t )
            {
                auto audio = AudioManager::getInstance( );
                audio->setSeVolume( t );
            };
            auto logo = Sprite::create( u8"res/texture/system/logo.se.png" );
            layout->setContentSize( Size( bar->getContentSize( ).width,
                                          bar->getContentSize( ).height + logo->getContentSize( ).height ) );
            listView->addChild( layout );
            layout->setScale( Lib::fitWidth( layout, listView->getContentSize( ).width ) );
            layout->setContentSize( layout->getContentSize( ) * layout->getScale( ) );
            layout->addChild( bar );
            layout->addChild( logo );

            bar->setAnchorPoint( Vec2( 0, 0 ) );
            logo->setAnchorPoint( Vec2( 0, 0 ) );

            logo->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
        }

        /**
         * ボイスの音量
         */
        {
            auto layout = ui::Layout::create( );

            auto bar = SlideBar::create( u8"voice" );
            bar->move = [ ] ( float t )
            {
                auto audio = AudioManager::getInstance( );
                audio->setVoiceVolume( t );
            };
            auto logo = Sprite::create( u8"res/texture/system/logo.voice.png" );

            auto createSampleVoiceAnimationSprite = [ = ]
            {
                auto scale = Director::getInstance( )->getContentScaleFactor( );

                auto path = u8"res/texture/system/button.samplevoice.animation.png";
                auto sprite = Sprite::create( path );
                auto size = sprite->getContentSize( );
                const int sx = 5;
                const int sy = 1;
                const auto parts = Size( size.width / sx, size.height / sy );
                sprite->setContentSize( parts );
                Vector<SpriteFrame*> frames;
                for ( int y = 0; y < sy; ++y )
                {
                    for ( int x = 0; x < sx; ++x )
                    {
                        auto rect = Rect( x * parts.width, y * parts.height, parts.width, parts.height );
                        frames.pushBack( SpriteFrame::create( path, rect ) );
                    }
                }
                auto animation = Animation::createWithSpriteFrames( frames, 0.25F );
                sprite->runAction( RepeatForever::create( Animate::create( animation ) ) );
                sprite->setAnchorPoint( Vec2( 0, 0 ) );


                return sprite;
            };

            auto button = ui::Button::create( u8"res/texture/system/button.samplevoice.png",
                                              u8"res/texture/system/button.samplevoice.select.png" );
            button->setPosition( Vec2( logo->getContentSize( ).width, bar->getContentSize( ).height ) );
            button->setAnchorPoint( Vec2( 0, 0 ) );
            button->addTouchEventListener( [ ] ( Ref* ref, ui::Widget::TouchEventType type )
            {
                if ( type != ui::Widget::TouchEventType::ENDED ) return;

                // ここでサンプルボイスを流す。
                auto audio = AudioManager::getInstance( );
                audio->playVoice( u8"sample.voice" );
            } );
            layout->addChild( button );

            layout->setContentSize( Size( bar->getContentSize( ).width,
                                          bar->getContentSize( ).height + logo->getContentSize( ).height ) );
            listView->addChild( layout );
            layout->setScale( Lib::fitWidth( layout, listView->getContentSize( ).width ) );
            layout->setContentSize( layout->getContentSize( ) * layout->getScale( ) );
            layout->addChild( bar );
            layout->addChild( logo );

            bar->setAnchorPoint( Vec2( 0, 0 ) );
            logo->setAnchorPoint( Vec2( 0, 0 ) );

            logo->setPosition( Vec2( 0, bar->getContentSize( ).height ) );
        }

        /**
         * 表示速度
         */
        {
            auto layout = ui::Layout::create( );

            auto bar = SlideBar::create( u8"novel.speed" );
            bar->slider->setMaxPercent( 20 );
            auto logo = Sprite::create( u8"res/texture/system/logo.novel.speed.png" );
            layout->setContentSize( Size( bar->getContentSize( ).width,
                                          bar->getContentSize( ).height + logo->getContentSize( ).height ) );
            listView->addChild( layout );
            layout->setScale( Lib::fitWidth( layout, listView->getContentSize( ).width ) );
            layout->setContentSize( layout->getContentSize( ) * layout->getScale( ) );
            layout->addChild( bar );
            layout->addChild( logo );

            bar->setAnchorPoint( Vec2( 0, 0 ) );
            logo->setAnchorPoint( Vec2( 0, 0 ) );

            logo->setPosition( Vec2( 0, bar->getContentSize( ).height ) );

            /**
             * 表示されるときの文字更新速度
             */
            {
                message->setAnchorPoint( Vec2( 0, 0 ) );
                message->setPosition( vo + Vec2( 0, 200 * message->getScale( ) / scale ) );
                addChild( message );

                auto test = Label::createWithTTF( u8"読み上げのテスト、速度はこんな感じです。", OptionalValues::fontName, OptionalValues::fontSize / message->getScale( ) );
                test->setTextColor( OptionalValues::fontColor );
                test->enableShadow( OptionalValues::fontShadowColor, Size( 2, -2 ), 2 );
                {
                    test->setPosition( message->getContentSize( ) * 0.5 );
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
                    OptionalValues::readOutSpeed = 0.2 - t;
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

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png",
                                          u8"res/texture/system/backbutton.select.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 0, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( auto ptr = getLayer<LayerCity>( ) )
                {
                    ptr->jsonRead( );
                }
                removeFromParentAndCleanup( true );
            }
        } );
        return button;
    }
    cocos2d::ui::Button * LayerOption::createDeleteButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/delete.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 1, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                addChild( createDialog( u8"最初から始めますか？\n保存したデータは残ります。", [ ]
                {
                    restart( );
                    SceneManager::createTitle( );
                }, [ ]
                {

                } ) );
            }
        } );
        return button;
    }
    cocos2d::Node * LayerOption::createModal( )
    {
        // 簡易的なモーダルレイヤーです。
        // 透明な画像を画面いっぱいに貼ることで機能しています。
        std::string dir = u8"res/texture/system/";
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto modal = ui::Button::create( dir + u8"null.png" );

        modal->setScale( vs.width * 0.5 * scale, vs.height * 0.5 * scale );
        modal->setPosition( vo + vs * 0.5 );

        return modal;
    }
    cocos2d::ui::Layout* LayerOption::createDialog( std::string const& str, std::function<void( )> const & yes, std::function<void( )> const & no )
    {
        auto layout = ui::Layout::create( );

        layout->addChild( createModal( ) );

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        //メニューの背景
        auto menuImage = ui::Scale9Sprite::create( u8"res/Image/WindowBase/WinBase_61.png",
                                                   Rect( 0 / scale, 0 / scale,
                                                         120 / scale, 120 / scale ),
                                                   Rect( 32 / scale, 32 / scale,
                                                         64 / scale, 64 / scale ) );

        auto content_size = Size( 640, 640 );
        menuImage->setContentSize( content_size );
        menuImage->setPosition( vo + vs * 0.5 );
        layout->addChild( menuImage );

        auto label = Label::createWithTTF( str, u8"res/fonts/HGRGE.TTC", 48 * scale );
        label->setPosition( content_size * 0.5 );
        menuImage->addChild( label );

        auto yes_button = ui::Button::create( u8"res/texture/system/yes.button.base.png", u8"res/texture/system/yes.button.push.png" );
        yes_button->setPosition( Vec2( content_size.width * 0.25, content_size.height * 0.1 ) );
        yes_button->setScale( Lib::fitWidth( yes_button, 150 ) );
        yes_button->setAnchorPoint( Vec2( 0.5, 0 ) );
        menuImage->addChild( yes_button );
        yes_button->addTouchEventListener( [ = ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            if ( yes )yes( );
            layout->removeFromParentAndCleanup( true );
        } );
        auto no_button = ui::Button::create( u8"res/texture/system/no.button.base.png", u8"res/texture/system/no.button.push.png" );
        no_button->setPosition( Vec2( content_size.width * 0.75, content_size.height * 0.1 ) );
        no_button->setAnchorPoint( Vec2( 0.5, 0 ) );
        no_button->setScale( Lib::fitWidth( no_button, 150 ) );
        menuImage->addChild( no_button );
        no_button->addTouchEventListener( [ = ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            if ( no )no( );
            layout->removeFromParentAndCleanup( true );
        } );

        return layout;
    }
    cocos2d::ui::Button * User::LayerOption::createSaveMenuButton( )
    {
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/icon.save.edge.png" );
        button->setAnchorPoint( Vec2( 1, 0 ) );
        button->setScale( Lib::fitHeight( button, 128 / scale ) );
        button->addTouchEventListener( [ this ] ( LAMBDA_TOUCH )
        {
            switch ( type )
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addChild( LayerSave::create( ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        } );
        return button;
    }
    SlideBar::SlideBar( )
    {
        std::string dir = u8"res/texture/system/";
        slider = ui::Slider::create( );

        auto left = ui::Button::create( u8"res/texture/system/slider.left.png", u8"res/texture/system/slider.left.select.png" );
        left->setAnchorPoint( Vec2( 0, 0 ) );
        addChild( left );
        auto translate = left->getContentSize( ).width;
        left->addTouchEventListener( [ this ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            switch ( type )
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                int value = clampf( slider->getPercent( ) - 1.0F, 0.0F, slider->getMaxPercent( ) );
                slider->setPercent( value );
                float percent = slider->getPercent( ) / 100.0F;
                if ( move ) move( percent );
                if ( ended ) ended( percent );
                if ( !key.empty( ) ) UserDefault::getInstance( )->setFloatForKey( key.c_str( ), percent );
            }
            break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        } );

        auto scale = Director::getInstance( )->getContentScaleFactor( );

        slider->loadBarTexture( dir + u8"slider.process.base.png" );
        slider->loadProgressBarTexture( dir + u8"slider.process.bar.png" );
        slider->loadSlidBallTextures( dir + u8"slider.button.png", dir + u8"slider.button.select.png" );
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
        slider->setAnchorPoint( Vec2( 0, 0 ) );
        slider->setContentSize( slider->getContentSize( ) + Size( 128 * 2, 128 ) * scale );
        slider->setPosition( Vec2( translate, 0 ) );
        translate += slider->getContentSize( ).width;

        auto right = ui::Button::create( u8"res/texture/system/slider.right.png", u8"res/texture/system/slider.right.select.png" );
        addChild( right );
        right->setAnchorPoint( Vec2( 0, 0 ) );
        right->setPosition( Vec2( translate, 0 ) );
        translate += right->getContentSize( ).width;
        right->addTouchEventListener( [ this ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            switch ( type )
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                float max = slider->getMaxPercent( );
                int value = clampf( slider->getPercent( ) + 1.0F, 0.0F, slider->getMaxPercent( ) );
                slider->setPercent( value );
                float percent = slider->getPercent( ) / 100.0F;
                if ( move ) move( percent );
                if ( ended ) ended( percent );
                if ( !key.empty( ) ) UserDefault::getInstance( )->setFloatForKey( key.c_str( ), percent );
            }
            break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        } );

        addChild( slider );

        setContentSize( Size( translate, slider->getContentSize( ).height ) );
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
