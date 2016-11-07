#include "BackLogLayer.h"

#include "NovelLayer.h"

#include "ui/CocosGUI.h"

#include "OptionalValues.h"

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
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_0 )
            {
                auto novelLayer = getLayer<NovelLayer>( );

                this->getEventDispatcher( )->pauseEventListenersForTarget( novelLayer );

                auto origin = Director::getInstance( )->getVisibleOrigin( );
                auto visibleSize = Director::getInstance( )->getVisibleSize( );
                auto contentScale = Director::getInstance( )->getContentScaleFactor( );

                auto layout = ui::Layout::create( );
                this->addChild( layout );
                layout->setName( u8"layout" );
                auto layoutSize = visibleSize;
                layout->setContentSize( layoutSize );

                auto closeButton = ui::Button::create( u8"res/Image/WindowBase/WinBase_18.png" );
                layout->addChild( closeButton );
                closeButton->setTitleFontSize( OptionalValues::fontSize );
                closeButton->setTitleText( u8"close" );
                closeButton->setPosition( origin + Vec2( visibleSize.width * 0.5, visibleSize.height * 0.15 ) );

                closeButton->addTouchEventListener( [ = ] ( Ref* pSender, ui::Widget::TouchEventType type )
                {
                    auto node = this->getChildByName( u8"layout" );
                    if ( type == ui::Widget::TouchEventType::ENDED )
                    {
                        this->removeChild( node );
                        this->getEventDispatcher( )->resumeEventListenersForTarget( novelLayer );
                    }
                } );

                auto menuImage = ui::Scale9Sprite::create( u8"res/Image/WindowBase/WinBase_58.png",
                                                           Rect( 0 / contentScale, 0 / contentScale,
                                                                 120 / contentScale, 120 / contentScale ),
                                                           Rect( 32 / contentScale, 32 / contentScale,
                                                                 64 / contentScale, 64 / contentScale ) );
                layout->addChild( menuImage );
                menuImage->setContentSize( Size( visibleSize.width * 0.9, visibleSize.height * 0.7 ) );
                menuImage->setPosition( origin + Size( visibleSize.width * 0.5, visibleSize.height * 0.5 + visibleSize.height *0.15 ) );

                auto list = ui::ListView::create( );
                menuImage->addChild( list );
                list->setContentSize( Size( visibleSize.width * 0.9, visibleSize.height * 0.7 ) );

                auto chunk = novelLayer->getTextChunkManager( ).getTextChunk( );

                for ( auto& novel : chunk )
                {
                    std::string log;
                    for ( auto& text : novel.getNovelData( ) )
                    {
                        log += text;
                    }

                    auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

                    auto button = ui::Button::create( u8"res/Image/WindowBase/WinBase_91.png" );

                    auto tar = OptionalValues::stringViewSize;
                    auto con = button->getContentSize( );
                    button->setTitleFontName( u8"res/fonts/meiryo.ttc" );
                    button->setTitleFontSize( OptionalValues::fontSize );
                    button->setTitleText( log );
                    list->addChild( button );
                }
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        return true;
    }
    void BackLogLayer::setup( )
    {

    }
}
