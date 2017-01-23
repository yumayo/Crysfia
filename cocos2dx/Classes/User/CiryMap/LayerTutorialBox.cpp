#include "LayerTutorialBox.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    bool LayerTutorialBox::init( std::string const & title, std::function<void( )> const & ok )
    {
        if ( !LayerColor::init( ) ) return false;

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;
        auto const fade_time = 0.2F;

        // 色は黒色
        setColor( Color3B::BLACK );

        // 初期状態ではレイヤーは透明。
        setOpacity( 0 );
        // フェードイン
        runAction( FadeTo::create( fade_time, 196 ) );

        auto sprite = Sprite::create( u8"res/texture/system/tutorial.box.png" );
        sprite->setPosition( vo + vs * 0.5 );
        sprite->setScale( Lib::fitWidth( sprite, vs.width * 0.9 ) );
        addChild( sprite );

        auto label = Label::createWithTTF( title,
                                           u8"res/fonts/HGRGE.TTC",
                                           64 );
        label->setTextColor( Color4B( 240, 240, 240, 255 ) );
        label->setScale( Lib::fitWidth( label, sprite->getContentSize( ).width * 0.9 ) );
        label->setPosition( sprite->getContentSize( ) * 0.5 );
        sprite->addChild( label );

        auto event = EventListenerTouchOneByOne::create( );
        event->setSwallowTouches( true );
        event->onTouchBegan = [this, fade_time, event, ok]( Touch* t, Event* e ) -> bool
        {
            if ( remove_started ) return true;
            remove_started = true;

            enumerateChildren( "//.*", [fade_time, event]( cocos2d::Node* child )
            {
                child->runAction( FadeOut::create( fade_time ) );
                return false;
            } );

            auto fade = FadeTo::create( fade_time, 0 );
            auto removeEvent = CallFunc::create( [this, event] { Director::getInstance( )->getEventDispatcher( )->removeEventListener( event ); } );
            auto ok_call = CallFunc::create( [ ok ] { if ( ok ) ok( ); } );
            runAction( Sequence::create( fade, removeEvent, ok_call, RemoveSelf::create( ), nullptr ) );
            return true;
        };
        Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( event, this );

        // 全ての子ノードをフェードインする。
        enumerateChildren( "//.*", [ fade_time ] ( cocos2d::Node* child )
        {
            child->setOpacity( 0 );
            child->runAction( FadeIn::create( fade_time ) );
            return false;
        } );

        return true;
    }
}
