#include "NameLayer.h"

#include "OptionalValues.h"

#include "../TouchiEvent/EventListenerGesture.h"

#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    NameLayer::NameLayer( )
    {

    }
    NameLayer::~NameLayer( )
    {

    }
    bool NameLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        return true;
    }
    void NameLayer::setup( )
    {

    }
    void NameLayer::addNovelWinodowSwitch( )
    {
        ScriptStaticData::run( { "sys", "noveloff" } );

        auto touchevent = EventListenerGesture::create( );
        touchevent->setSwallowTouches( true );

        touchevent->onTap = [ this, touchevent ] ( Vec2 pos )
        {
            scheduleOnce( [ this, touchevent ] ( float delay )
            {
                ScriptStaticData::run( { "sys", "novelon" } );
                getEventDispatcher( )->removeEventListener( touchevent );
            }, 0.01F, typeid( this ).name( ) );
        };
        getEventDispatcher( )->addEventListenerWithFixedPriority( touchevent, -1 );
    }
    void NameLayer::on( )
    {
        this->setVisible( true );
    }
    void NameLayer::off( )
    {
        this->setVisible( false );
    }
    void NameLayer::in( )
    {
        enumerateChildren( "//.*", [ ] ( cocos2d::Node* node )
        {
            node->runAction( FadeIn::create( 0.3F ) );
            return false;
        } );
    }
    void NameLayer::out( )
    {
        enumerateChildren( "//.*", [ ] ( cocos2d::Node* node )
        {
            node->runAction( FadeOut::create( 0.3F ) );
            return false;
        } );
    }
}
