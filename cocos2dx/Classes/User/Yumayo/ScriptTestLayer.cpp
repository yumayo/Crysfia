#include "ScriptTestLayer.h"

USING_NS_CC;

bool ScriptTestLayer::init( )
{
    if ( !Layer::init( ) ) return false;

    // アップデートを呼ぶため。
    this->scheduleUpdate( );

    windowDefineUpdate( );

    mouseEvent = EventListenerMouse::create( );
    mouseEvent->onMouseMove = [ this ] ( EventMouse* event )
    {
        mousePosition.x = event->getCursorX( );
        mousePosition.y = event->getCursorY( );
    };
    mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
    {
        if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
        {
            if ( textLabels.getIsReadOuted( ) )
            {
                textChank.clear( );
                textLabels.clear( );

                textLabels.layerPeelOff( this );
                while ( !textChank.isNext( ) )
                {
                    textChank.insertScript( reader.createTagRawScriptData( textData.getLineMoved( ) ) );
                }
                auto size = Size( origin + visibleSize );
                textLabels.setStrings( textChank.getNovelData( ), Vec2( size.width * 0.5 - size.width * 0.7 / 2, size.height * 0.2 ) );
                textLabels.layerPasting( this );
            }
            else
            {
                textLabels.actionStop( );
            }
        }
    };
    this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );


    auto label = Label::createWithTTF( u8"ScriptTestLayer", "fonts/Marker Felt.ttf", 24 );
    label->setPosition( Vec2( origin.x + visibleSize.width / 2,
                              origin.y + visibleSize.height - label->getContentSize( ).height ) );
    this->addChild( label, 1000 );

    textChank.clear( );
    textLabels.layerPeelOff( this );
    //textLabels.releace( );
    while ( !textChank.isNext( ) )
    {
        textChank.insertScript( reader.createTagRawScriptData( textData.getLineMoved( ) ) );
    }
    auto size = Size( origin + visibleSize );
    textLabels.setStrings( textChank.getNovelData( ), Vec2( size.width * 0.5 - size.width * 0.7 / 2, size.height * 0.2 ) );
    textLabels.layerPasting( this );

    return true;
}
void ScriptTestLayer::cleanup( )
{
    this->getEventDispatcher( )->removeEventListener( mouseEvent );
}
void ScriptTestLayer::windowDefineUpdate( )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}
void ScriptTestLayer::update( float delta )
{
    windowDefineUpdate( );
}
