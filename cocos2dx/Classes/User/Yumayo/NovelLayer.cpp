#include "NovelLayer.h"

#include "OptionalValues.h"

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

        keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 ) setup( );
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        mouseEvent = EventListenerMouse::create( );
        mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        {
            if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
            {
                if ( textLabels.getIsReadOuted( ) ) textUpdate( );
                else textLabels.actionStop( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

        return true;
    }
    void NovelLayer::setup( )
    {
        textData.makeData( "script.txt" );
        textUpdate( );
    }
    void NovelLayer::textUpdate( )
    {
        textChank.clear( );
        textLabels.clear( );
        while ( !textChank.isNext( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagRawScriptPartsData( textData.getLineMoved( ) ) );
        }
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChank.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
}
