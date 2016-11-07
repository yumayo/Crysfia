
#include "LayerIsland.h"

#include "../SceneManager.h"

#include "../Yumayo/OptionalValues.h"

#include <vector>
#include <functional>

USING_NS_CC;

namespace User
{
    LayerIsland::LayerIsland( )
    {
    }
    LayerIsland::~LayerIsland( )
    {
    }
    bool LayerIsland::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        initListener( );

        initBackground( );

        initCountry( );

        this->addChild( createDebugButton( ) );

        return true;
    }
    void LayerIsland::setup( )
    {

    }
    void LayerIsland::update( float delta )
    {

    }
    void LayerIsland::initBackground( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        background = Sprite::create( u8"res/texture/全体マップ.png" );

        translate = origin + visibleSize / 2;
        targetSize = visibleSize;
        backgroundWindowHeightFitScale = targetSize.height / background->getContentSize( ).height;

        background->setPosition( translate );
        background->setScale( backgroundWindowHeightFitScale, backgroundWindowHeightFitScale );

        this->addChild( background );
    }
    void LayerIsland::initCountry( )
    {
        auto s = background->getContentSize( );

        auto layout = ui::Layout::create( );
        background->addChild( layout );

        auto createButton = [ & ] ( float x, float y, std::string const& novel )
        {
            auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
            x *= scale; y *= scale;

            auto button = ui::Button::create( u8"res/Image/WindowBase/WinBase_91.png" );
            layout->addChild( button );

            button->setPosition( Vec2( x, s.height - y ) );
            auto tar = Size( 64, 64 );
            auto con = button->getContentSize( );
            auto sca = tar.height / con.height;
            button->setScale( sca, sca );
            button->addTouchEventListener( [ this, layout, novel ] ( Ref* pSender, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::ENDED )
                {
                    layout->setEnabled( false );
                    SceneManager::createCiryMap( novel );
                }
            } );
        };

        createButton( 206, 510, u8"ミニマップ.png" );
        createButton( 314, 374, u8"ミニマップ.png" );
        createButton( 567, 482, u8"ミニマップ.png" );
        createButton( 618, 366, u8"ミニマップ.png" );
        createButton( 803, 582, u8"ミニマップ.png" );
        createButton( 788, 312, u8"ミニマップ.png" );
    }
    void LayerIsland::initListener( )
    {
        auto listener = EventListenerTouchAllAtOnce::create( );
        listener->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        listener->onTouchesMoved = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );

            auto texS_2 = ( background->getContentSize( ) * backgroundWindowHeightFitScale ) / 2;
            auto winS_2 = visibleSize / 2;
            auto clearance = texS_2 - winS_2;

            for ( auto& obj : touches )
            {
                auto movedPos = background->getPosition( ) - translate + obj->getDelta( );
                movedPos.clamp( clearance * -1, clearance );
                background->setPosition( movedPos + translate );
            }
        };
        listener->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( listener, this );
    }
    cocos2d::ui::Button* LayerIsland::createDebugButton( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto button = ui::Button::create( u8"res/Image/WindowBase/WinBase_104.png" );
        button->setTitleFontName( u8"res/fonts/meiryo.ttc" );
        button->setTitleFontSize( OptionalValues::fontSize );
        button->setTitleText( u8"DEBUG" );
        button->setPosition( origin + visibleSize - button->getContentSize( ) / 2.0 );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                isDebug = !isDebug;
                auto but = dynamic_cast<ui::Button*>( pSender );
                if ( but )
                {
                    if ( isDebug ) but->loadTextureNormal( u8"res/Image/WindowBase/WinBase_64.png" );
                    else but->loadTextureNormal( u8"res/Image/WindowBase/WinBase_104.png" );
                }
            }
        } );
        return button;
    }
}
