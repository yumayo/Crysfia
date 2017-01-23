#include "ModalLayer.h"

USING_NS_CC;

namespace User
{
    bool ModalLayer::init( )
    {
        if ( !Layer::init( ) )
        {
            return false;
        }

        auto touch = EventListenerTouchOneByOne::create( );

        auto multi = EventListenerTouchAllAtOnce::create( );
        multi->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };

        auto key = EventListenerKeyboard::create( );
        key->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {

        };

        auto mouse = EventListenerMouse::create( );
        mouse->onMouseDown = [ this ] ( EventMouse* event )
        {

        };
        mouse->checkAvailable( );

        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( multi, this );
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( key, this );
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouse, this );
        this->getEventDispatcher( )->setPriority( mouse, -1 );
        this->getEventDispatcher( )->setEnabled( false );

        return true;
    }
}
