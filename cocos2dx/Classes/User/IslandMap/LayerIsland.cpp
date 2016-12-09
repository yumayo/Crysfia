
#include "LayerIsland.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include "../Live2d/LAppView.h"

#include <vector>
#include <functional>

#include "../../Lib/Utility/Utilitys.h"

USING_NS_CC;

namespace User
{
    void Mark::pasteMap( cocos2d::Sprite * map, CityPointData const & data )
    {
        initData( data );

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
        auto pixel = map->getContentSize( ) / scale;

        map->addChild( this );

        setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
        setScale( Lib::fitWidth( this, 64 * scale ), Lib::fitWidth( this, 64 * scale ) );

        addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                map->pause( );
                SceneManager::createCityMap( this->path );
            }
        } );
    }

    void CityMark::pasteMap( cocos2d::Sprite * map, CityPointData const & data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + u8"castle.png" );

        Mark::pasteMap( map, data );
    }

    IslandMap * IslandMap::make( )
    {
        const std::string dir = u8"res/texture/system/";

        initWithFile( dir + u8"worldmap.png" );

        auto size = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto targetSize = size;
        translate = origin + size / 2;
        auto backgroundWindowHeightFitScale = targetSize.height / getContentSize( ).height;

        setPosition( translate );
        setScale( backgroundWindowHeightFitScale, backgroundWindowHeightFitScale );

        auto listener = EventListenerTouchAllAtOnce::create( );
        listener->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        listener->onTouchesMoved = [ this, backgroundWindowHeightFitScale ] ( const std::vector<Touch*>& touches, Event* event )
        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );

            auto texS_2 = ( getContentSize( ) * backgroundWindowHeightFitScale ) / 2;
            auto winS_2 = visibleSize / 2;
            auto clearance = texS_2 - winS_2;

            for ( auto& obj : touches )
            {
                auto movedPos = getPosition( ) - translate + obj->getDelta( );
                if ( clearance.width * -1 <= clearance.width &&
                     clearance.height * -1 <= clearance.height )
                {
                    movedPos.clamp( clearance * -1, clearance );
                    setPosition( movedPos + translate );
                }
            }
        };
        listener->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( listener, this );

        return this;
    }

    LayerIsland::LayerIsland( )
    {
    }
    LayerIsland::~LayerIsland( )
    {
    }
    bool LayerIsland::init( )
    {
        if ( !Layer::init( ) ) return false;

        auto background = IslandMap::create( )->make( );
        this->addChild( background );

        CityMark::create( )->pasteMap( background, { cocos2d::Vec2( 206, 510 ), u8"island.json" } );
        CityMark::create( )->pasteMap( background, { cocos2d::Vec2( 314, 374 ), u8"island.json" } );
        CityMark::create( )->pasteMap( background, { cocos2d::Vec2( 567, 482 ), u8"island.json" } );
        CityMark::create( )->pasteMap( background, { cocos2d::Vec2( 618, 366 ), u8"island.json" } );
        CityMark::create( )->pasteMap( background, { cocos2d::Vec2( 803, 582 ), u8"island.json" } );

        return true;
    }
    void LayerIsland::setup( )
    {

    }
}
