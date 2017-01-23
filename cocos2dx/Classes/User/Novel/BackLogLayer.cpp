#include "BackLogLayer.h"

#include "NovelLayer.h"
#include "NameLayer.h"

#include "FlickFunctionLayer.h"

#include "ui/CocosGUI.h"

#include "OptionalValues.h"

#include "ScriptStaticData.h"

#include "../../Lib/Utilitys.h"

#include "../TouchiEvent/EventListenerGesture.h"

USING_NS_CC;

namespace User
{
    BackLogLayer::BackLogLayer( )
    {

    }
    BackLogLayer::~BackLogLayer( )
    {

    }
    bool BackLogLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        auto keyEvent = EventListenerKeyboard::create( );

        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_0 )
            {
                showBacklog( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        return true;
    }
    void BackLogLayer::setup( )
    {

    }
    void BackLogLayer::showBacklog( )
    {
        if ( isBacklog ) return;
        isBacklog = true;

        auto novelLayer = getLayer<NovelLayer>( );

        ScriptStaticData::run( { "sys", "noveldisable" } );

        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto contentScale = Director::getInstance( )->getContentScaleFactor( );

        auto layout = ui::Layout::create( );
        this->addChild( layout );
        layout->setName( u8"layout" );
        layout->setContentSize( visibleSize );

        auto menuImage = ui::Scale9Sprite::create( u8"res/Image/WindowBase/WinBase_58.png",
                                                   Rect( 0 / contentScale, 0 / contentScale,
                                                         120 / contentScale, 120 / contentScale ),
                                                   Rect( 32 / contentScale, 32 / contentScale,
                                                         64 / contentScale, 64 / contentScale ) );
        layout->addChild( menuImage );
        menuImage->setContentSize( visibleSize );
        menuImage->setPosition( origin + visibleSize * 0.5 );
        auto menuImageSize = menuImage->getContentSize( );

        auto listView = ui::ListView::create( );
        menuImage->addChild( listView );
        listView->setContentSize( Size( menuImageSize.width, menuImageSize.height ) );
        auto listViewSize = listView->getContentSize( );

        auto chunk = novelLayer->getTextChunkManager( ).getTextChunk( );

        for ( auto& novel : chunk )
        {
            auto chunkLayout = ui::Layout::create( );
            listView->addChild( chunkLayout );
            chunkLayout->setContentSize( Size( listViewSize.width, OptionalValues::stringViewSize.y * 0.9 ) );
            auto chunkLayoutSize = chunkLayout->getContentSize( );

            size_t index = 0;
            for ( auto& text : novel.getNovelData( ) )
            {
                auto novelLayout = ui::Layout::create( );
                chunkLayout->addChild( novelLayout );
                novelLayout->setContentSize( Size( chunkLayoutSize.width * 0.9, OptionalValues::fontSize * 0.9 + OptionalValues::lineSpaceSize * 0.9 ) );
                auto novelLayoutSize = novelLayout->getContentSize( );
                novelLayout->setPosition( Vec2( novelLayoutSize.width * 0.05, 0 ) );

                auto label = Label::createWithTTF( text, OptionalValues::fontName, OptionalValues::fontSize * 0.9 );
                novelLayout->addChild( label );

                auto contentWidth = label->getContentSize( ).width;
                if ( novelLayoutSize.width <= contentWidth )
                {
                    label->setScaleX( novelLayoutSize.width / contentWidth );
                }

                float width;
                auto contentSize = label->getContentSize( );
                if ( novelLayoutSize.width <= contentSize.width ) width = novelLayoutSize.width * 0.5;
                else width = contentSize.width * 0.5;

                label->setPosition( Vec2( width, -contentSize.height - novelLayoutSize.height * index ) );
                index++;
            }
        }
        listView->jumpToBottom( );

        auto touchevent = EventListenerGesture::create( );
        touchevent->onTap = [ this, layout, touchevent ] ( Vec2 pos )
        {
            removeChild( layout );
            isBacklog = false;

            scheduleOnce( [ this, touchevent ] ( float delay )
            {
                ScriptStaticData::run( { "sys", "novelenable" } );
                getEventDispatcher( )->removeEventListener( touchevent );
            }, 0.0F, typeid( this ).name( ) );
        };
        getEventDispatcher( )->addEventListenerWithFixedPriority( touchevent, -1 );
    }
}
