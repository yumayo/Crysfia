
#include "LayerNovelView.h"

#include "../SceneManager.h"
#include "../../Lib/Utilitys.h"
#include "../../Lib/AudioManager.h"

USING_NS_CC;

namespace User
{
    LayerNovelView * LayerNovelView::create( ScenarioPointData const& scenario, std::function<void( )> const& saveCallFunc )
    {
        LayerNovelView *pRet = new( std::nothrow ) LayerNovelView( );
        if ( pRet && pRet->init( scenario, saveCallFunc ) )
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
    bool LayerNovelView::init( ScenarioPointData const& scenario, std::function<void( )> const& saveCallFunc )
    {
        if ( !cocos2d::LayerColor::init( ) ) return false;

        const auto vs = Director::getInstance( )->getVisibleSize( );
        const auto vo = Director::getInstance( )->getVisibleOrigin( );
        const auto scale = Director::getInstance( )->getContentScaleFactor( );
        const auto _scale = 1.0F / scale;
        const float fadeTime = 0.2F;

        // 色は黒色
        setColor( Color3B::BLACK );

        // 初期状態ではレイヤーは透明。
        setOpacity( 0 );
        // フェードイン
        runAction( FadeTo::create( fadeTime, 196 ) );


        // タップしたら、フェードアウトしてレイヤーを削除する。
        // ダブルタップを防ぐために、一度押されたら、eventを無効にする。
        auto event = EventListenerTouchOneByOne::create( );
        event->setSwallowTouches( true );
        event->onTouchBegan = [this, event, fadeTime, scenario]( Touch* t, Event* e )
        {
            if ( isNext ) return true;

            // 強制イベントは無効に出来ない。
            if ( !UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) )
            {
                if ( scenario.event == ScenarioPointData::Event::force ) return true;
            }

            enumerateChildren( "//.*", [ fadeTime ] ( cocos2d::Node* child )
            {
                child->runAction( FadeOut::create( fadeTime ) );
                return false;
            } );

            auto fade = FadeTo::create( fadeTime, 0 );
            auto removeEvent = CallFunc::create( [event] { Director::getInstance( )->getEventDispatcher( )->removeEventListener( event ); } );
            runAction( Sequence::create( fade, removeEvent, RemoveSelf::create( ), nullptr ) );
            return true;
        };
        Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( event, this );

        // ボードはど真ん中に設置。
        auto next_stage = Sprite::create( u8"res/texture/system/next.stage.png" );
        next_stage->setPosition( vo + vs * 0.5 );
        next_stage->setScale( scale );
        addChild( next_stage );

        int dead_line = scenario.get_dead_line( );
        bool stay = scenario.is_stay( );
        std::string stay_day;
        if ( UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) )
        {
            if ( scenario.visit )
            {
                stay_day = u8"既読";
            }
            else
            {
                stay_day = u8"未読";
            }
        }
        else if ( dead_line == 0 && stay )
        {
            // 当日 最終日
            stay_day = u8"今日まで";
        }
        else
        {
            stay_day = StringUtils::format( u8"あと%d日", dead_line );
        }
        auto label_event_name = Label::createWithTTF( stay_day,
                                                      u8"res/fonts/HGRGE.TTC",
                                                      32 );
        label_event_name->setScale( Lib::fitHeight( label_event_name, 32 * _scale ) );
        label_event_name->setPosition( Vec2( 367, 230 - 100 ) * _scale );
        next_stage->addChild( label_event_name );

        std::string event_name_path;
        switch ( scenario.event )
        {
        case ScenarioPointData::Event::force:
            event_name_path = u8"force";
            break;
        case ScenarioPointData::Event::main:
            event_name_path = u8"main";
            break;
        case ScenarioPointData::Event::sub:
            event_name_path = u8"sub";
            break;
        default:
            break;
        }
        auto event_name = Sprite::create( u8"res/texture/system/event." + event_name_path + u8".png" );
        event_name->setPosition( Vec2( 285, 230 - 46 ) * _scale );
        next_stage->addChild( event_name );

        if ( scenario.morning )
        {
            auto morning = Sprite::create( u8"res/texture/system/time.1.check.png" );
            morning->setPosition( Vec2( 145, 230 - 100 ) * _scale );
            next_stage->addChild( morning );
        }
        if ( scenario.daytime )
        {
            auto daytime = Sprite::create( u8"res/texture/system/time.2.check.png" );
            daytime->setPosition( Vec2( 195, 230 - 100 ) * _scale );
            next_stage->addChild( daytime );
        }
        if ( scenario.night )
        {
            auto night = Sprite::create( u8"res/texture/system/time.3.check.png" );
            night->setPosition( Vec2( 245, 230 - 100 ) * _scale );
            next_stage->addChild( night );
        }

        // タイトル //
        // タイトルはマスクで切り取りたい。
        // ここからマスクの処理を書きます。
        Vec2 title_start_pos( 20, 200 );
        Size title_size( 431, 67 );
        if ( auto clipping = ClippingNode::create( ) )
        {
            clipping->setInverted( false );
            clipping->setAlphaThreshold( 0.0 );
            clipping->setAnchorPoint( Vec2( 0, 0 ) );
            clipping->setPosition( Vec2( title_start_pos.x, 230 - title_start_pos.y ) * _scale );

            if ( auto mask = Sprite::create( ) )
            {
                mask->setTextureRect( Rect( 0, 0, title_size.width * _scale, title_size.height * _scale ) );
                mask->setAnchorPoint( Vec2( 0, 0 ) );
                clipping->setStencil( mask );
            }

            // タイトルは長くて見切れることのほうが多いと思うので、
            // ニコニコ動画の記事のように、一定時間でスライドするようにする。
            if ( auto title_label = Label::createWithTTF( scenario.title,
                                                          u8"res/fonts/HGRGE.TTC",
                                                          48 * _scale ) )
            {
                title_label->setAnchorPoint( Vec2( 0, 0 ) );
                title_label->setTextColor( Color4B( 242, 242, 242, 255 ) ); // 白
                auto title_label_translate_y = ( title_size.height * 0.5F - 48 * 0.5F ) * _scale;
                title_label->setPosition( Vec2( 0, title_label_translate_y ) );

                const auto slide = title_label->getContentSize( ).width - title_size.width * _scale;
                auto action = title_label->getContentSize( ).width < title_size.width * _scale
                    ? Sequence::create( DelayTime::create( 2.5F ), // 止める
                                        // MoveTo::create( ( title_label->getContentSize( ).width - 420 * _scale ) * 0.01, Vec2( -slide, 0 ) ),
                                        DelayTime::create( 2.5F ),
                                        MoveTo::create( 0.3F, Vec2( -title_label->getContentSize( ).width, title_label_translate_y ) ),
                                        CallFunc::create( [ title_label, title_label_translate_y ] { title_label->setPosition( Vec2( title_label->getContentSize( ).width,
                                                                                                                                     title_label_translate_y ) ); } ),
                                        MoveTo::create( 0.3F, Vec2( 0, title_label_translate_y ) ),
                                        nullptr )
                    : Sequence::create( DelayTime::create( 2.5F ), // 止める
                                        MoveTo::create( ( title_label->getContentSize( ).width - title_size.width * _scale ) * 0.01, Vec2( -slide, title_label_translate_y ) ),
                                        DelayTime::create( 2.5F ),
                                        MoveTo::create( 0.3F, Vec2( -title_label->getContentSize( ).width, title_label_translate_y ) ),
                                        CallFunc::create( [ title_label, title_label_translate_y ] { title_label->setPosition( Vec2( title_label->getContentSize( ).width,
                                                                                                                                     title_label_translate_y ) ); } ),
                                        MoveTo::create( 0.3F, Vec2( 0, title_label_translate_y ) ),
                                        nullptr );
                title_label->runAction( RepeatForever::create( action ) );

                clipping->addChild( title_label );
            }
            next_stage->addChild( clipping );
        }

        // アイテム情報はまだ未定 //

        // 決定ボタン //
        if ( auto okButton = ui::Button::create( u8"res/texture/system/ok.button.png",
                                                 u8"res/texture/system/ok.button.select.png" ) )
        {
            okButton->setAnchorPoint( Vec2( 0.5F, 0.5F ) );
            okButton->setPosition( vo + Vec2( 454, 230 - 213 ) * _scale + okButton->getContentSize( ) * 0.5 );
            okButton->runAction( RepeatForever::create( Sequence::create( EaseSineOut::create( ScaleTo::create( 0.75F, 1.1F ) ), EaseSineIn::create( ScaleTo::create( 0.75F, 1.0F ) ), nullptr ) ) );
            okButton->addTouchEventListener( [ this, okButton, scenario, saveCallFunc ] ( Ref* ref, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::BEGAN )
                {
                    okButton->setScale( 1.0F );
                    okButton->stopAllActions( );
                }

                if ( type == ui::Widget::TouchEventType::CANCELED )
                {
                    okButton->runAction( RepeatForever::create( Sequence::create( EaseSineOut::create( ScaleTo::create( 0.75F, 1.1F ) ), EaseSineIn::create( ScaleTo::create( 0.75F, 1.0F ) ), nullptr ) ) );
                }

                if ( type != ui::Widget::TouchEventType::ENDED ) return;

                // 二度押せないように。
                if ( isNext ) return;

                AudioManager::getInstance( )->playSe( u8"res/sound/scenario_start.mp3" );

                runAction( CallFunc::create( [ this, okButton, scenario, saveCallFunc ]
                {
                    // フェードアウト
                    if ( auto sprite = Sprite::create( ) )
                    {
                        sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                        sprite->setAnchorPoint( Vec2( 0, 0 ) );
                        sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                        sprite->setOpacity( 0 );
                        sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this, scenario, saveCallFunc ]
                        {
                            SceneManager::createNovel( scenario.scenario, saveCallFunc );
                        } ), RemoveSelf::create( ), nullptr ) );
                        addChild( sprite );
                    }
                } ) );

                okButton->pause( );
                isNext = true;
            } );
            next_stage->addChild( okButton );
        }

        // 全ての子ノードをフェードインする。
        enumerateChildren( "//.*", [ fadeTime ] ( cocos2d::Node* child )
        {
            child->setOpacity( 0 );
            child->runAction( FadeIn::create( fadeTime ) );
            return false;
        } );

        return true;
    }
}
