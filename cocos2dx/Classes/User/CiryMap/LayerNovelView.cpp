
#include "LayerNovelView.h"

#include "../SceneManager.h"

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
            if ( scenario.event == ScenarioPointData::Event::force ) return true;

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

        // どんなイベントなのかを記入します。
        std::string event_name;
        switch ( scenario.event )
        {
        case ScenarioPointData::Event::force:
            event_name = u8"強制イベント";
            break;
        case ScenarioPointData::Event::main:
            event_name = u8"メインイベント";
            break;
        case ScenarioPointData::Event::sub:
            event_name = u8"サブイベント";
            break;
        default:
            break;
        }
        auto label_event_name = Label::createWithTTF( event_name,
                                                      u8"res/fonts/HGRGE.TTC",
                                                      64 * _scale );
        label_event_name->setAnchorPoint( Vec2( 0.5F, 0 ) );
        label_event_name->setPosition( Vec2( 273, 230 - 107 ) * _scale );
        next_stage->addChild( label_event_name );

        // タイトル //
        // タイトルはマスクで切り取りたい。
        // ここからマスクの処理を書きます。
        if ( auto clipping = ClippingNode::create( ) )
        {
            clipping->setInverted( false );
            clipping->setAlphaThreshold( 0.0 );
            clipping->setAnchorPoint( Vec2( 0, 0 ) );
            clipping->setPosition( Vec2( 28, 230 - 192 ) * _scale );

            if ( auto mask = Sprite::create( ) )
            {
                mask->setTextureRect( Rect( 0, 0, 420 * _scale, 48 * _scale ) );
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

                const auto slide = title_label->getContentSize( ).width - 420 * _scale;
                auto action = title_label->getContentSize( ).width < 420 * _scale
                    ? Sequence::create( DelayTime::create( 2.5F ), // 止める
                                        // MoveTo::create( ( title_label->getContentSize( ).width - 420 * _scale ) * 0.01, Vec2( -slide, 0 ) ),
                                        DelayTime::create( 2.5F ),
                                        MoveTo::create( 0.3F, Vec2( -title_label->getContentSize( ).width, 0 ) ),
                                        CallFunc::create( [ title_label ] { title_label->setPosition( Vec2( title_label->getContentSize( ).width, 0 ) ); } ),
                                        MoveTo::create( 0.3F, Vec2( 0, 0 ) ),
                                        nullptr )
                    : Sequence::create( DelayTime::create( 2.5F ), // 止める
                                        MoveTo::create( ( title_label->getContentSize( ).width - 420 * _scale ) * 0.01, Vec2( -slide, 0 ) ),
                                        DelayTime::create( 2.5F ),
                                        MoveTo::create( 0.3F, Vec2( -title_label->getContentSize( ).width, 0 ) ),
                                        CallFunc::create( [ title_label ] { title_label->setPosition( Vec2( title_label->getContentSize( ).width, 0 ) ); } ),
                                        MoveTo::create( 0.3F, Vec2( 0, 0 ) ),
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
            okButton->setAnchorPoint( Vec2( 0.0F, 0.0F ) );
            okButton->setPosition( vo + Vec2( 454, 230 - 213 ) * _scale );
            okButton->addTouchEventListener( [ this, okButton, scenario, saveCallFunc ] ( Ref* ref, ui::Widget::TouchEventType type )
            {
                if ( type != ui::Widget::TouchEventType::ENDED ) return;

                // 二度押せないように。
                if ( isNext ) return;

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
