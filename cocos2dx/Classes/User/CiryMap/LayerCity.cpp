#include "LayerCity.h"

#include "../SceneManager.h"

#include "../Yumayo/OptionalValues.h"

#include <vector>
#include <functional>

USING_NS_CC;

namespace User
{
    LayerCity::LayerCity( std::string const& backgroundPath )
        : backgroundPath( backgroundPath )
    {
    }
    LayerCity::~LayerCity( )
    {
    }
    bool LayerCity::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        initListener( );

        initBackground( );

        initCountry( );

        this->addChild( createDebugButton( ) );

        return true;
    }
    void LayerCity::setup( )
    {

    }
    void LayerCity::update( float delta )
    {

    }
    void LayerCity::initBackground( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        background = Sprite::create( u8"res/texture/" + backgroundPath );

        translate = origin + visibleSize / 2;
        targetSize = visibleSize;
        backgroundWindowHeightFitScale = targetSize.height / background->getContentSize( ).height;

        background->setPosition( translate );
        background->setScale( backgroundWindowHeightFitScale, backgroundWindowHeightFitScale );

        this->addChild( background );
    }
    void LayerCity::initCountry( )
    {
        auto s = background->getContentSize( );

        auto layout = ui::Layout::create( );
        background->addChild( layout );

        auto createButton = [ & ] ( float x, float y, std::string const& name, std::string const& novel )
        {
            auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
            x *= scale; y *= scale;

            auto button = ui::Button::create( name );
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
                    SceneManager::createNovel( novel );
                }
            } );
        };

        createButton( 155, 384, u8"res/Image/WindowBase/WinBase_91.png", u8"scenario1.txt" );
        createButton( 167, 201, u8"res/Image/WindowBase/WinBase_89.png", u8"scenario2.txt" );
        createButton( 342, 102, u8"res/Image/WindowBase/WinBase_90.png", u8"scenario3.txt" );
        createButton( 374, 248, u8"res/Image/WindowBase/WinBase_91.png", u8"scenario1.txt" );
    }
    void LayerCity::initListener( )
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
    cocos2d::ui::Button* LayerCity::createDebugButton( )
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
