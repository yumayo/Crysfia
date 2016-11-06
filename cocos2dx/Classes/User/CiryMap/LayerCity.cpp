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

        std::vector<ui::Button*> buttons;
        auto createButton = [ & ] ( float x, float y )
        {
            auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
            x *= scale; y *= scale;

            buttons.emplace_back( ui::Button::create( u8"res/Image/WindowBase/WinBase_91.png" ) );
            background->addChild( buttons.back( ) );
            buttons.back( )->setPosition( Vec2( x, s.height - y ) );
            auto tar = Size( 64, 64 );
            auto con = buttons.back( )->getContentSize( );
            auto sca = tar.height / con.height;
            buttons.back( )->setScale( sca, sca );
        };
        auto endedCallBack = [ & ] ( ui::Button* button, std::function<void( )> call )
        {
            button->addTouchEventListener( [ this, call ] ( Ref* pSender, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::ENDED )
                {
                    call( );
                }
            } );
        };

        createButton( 155, 384 );
        createButton( 167, 201 );
        createButton( 342, 102 );
        createButton( 374, 248 );

        for ( auto& button : buttons )
            endedCallBack( button, [ this ] 
        { 
            if ( isSelectCity ) return;
            isSelectCity = true;
            SceneManager::createNovel( u8"scenario1.txt" );
        } );
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
