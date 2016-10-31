#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

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

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                textData.makeData( "scenario1.txt" );
                textUpdate( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto mouseEvent = EventListenerMouse::create( );
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
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( origin.x, origin.y, visibleSize.width, OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        square->setPosition( rect.origin + rect.size / 2 );
        this->addChild( square );

        textData.makeData( "scenario1.txt" );
        textUpdate( );
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );
        selectLayer->removeAllChildren( );

        textData.setNextChild( name );
    }
    void NovelLayer::textUpdate( )
    {
        textChank.clear( );
        textLabels.clear( );
        while ( !textChank.isNext( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
        }
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChank.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
}
