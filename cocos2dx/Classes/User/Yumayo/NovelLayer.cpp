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

        scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                textData.makeData( "scenario1.txt" );
                textUpdate( );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                switchIsReadingProceed( );
            }
        };

        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                switchIsReadingProceed( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto mouseEvent = EventListenerMouse::create( );
        mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        {
            if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
            {
                // テキストをすでに読み込んでいる場合
                if ( textLabels.getIsReadOuted( ) )
                {
                    switchIsSystemRead( );
                    textUpdate( );
                }
                // テキストを読み込み途中の場合
                else
                {
                    // これで、読み込みが完了するまで処理を飛ばす。
                    switchIsSystemRead( );
                    textLabels.actionStop( );
                }
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
    void NovelLayer::update( float delta )
    {
        if ( isReadingProceed )
        {
            textUpdate( );
        }
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );

        switchIsNextText( );

        selectLayer->removeAllChildren( );

        textData.setNextChild( name );

        textUpdate( );
    }
    void NovelLayer::textUpdate( )
    {
        if ( !isNextText ) return;

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
