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
                layout->setContentSize( visibleSize );

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
                menuImage->setPosition( origin + Size( visibleSize.width * 0.5, visibleSize.height * 0.5 + visibleSize.height * 0.15 ) );
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

                        auto label = Label::createWithTTF( text, u8"res/fonts/F910MinchoW3.otf", OptionalValues::fontSize * 0.9 );
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
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        return true;
    }
    void BackLogLayer::setup( )
    {

    }
}
