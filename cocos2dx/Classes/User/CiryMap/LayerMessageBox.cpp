#include "LayerMessageBox.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    bool LayerMessageBox::init( std::string const & message, std::function<void( )> const & ok )
    {
        if ( !Sprite::init( ) ) return false;

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;
        auto const fade_time = 0.3F;

        initWithFile( u8"res/texture/system/message.box.png" );
        setPosition( vo + Vec2( vs.width * 0.5, vs.height * 0.75 ) );

        auto label = Label::createWithTTF( message,
                                           u8"res/fonts/HGRGE.TTC",
                                           64 );
        label->setScale( Lib::fitHeight( label, 64 * scale ) );
        label->setAnchorPoint( Vec2( 0, 0 ) );

        auto event = EventListenerTouchOneByOne::create( );
        Director::getInstance( )->getEventDispatcher( )->addEventListenerWithFixedPriority( event, -1 );
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

        return true;
    }
}
