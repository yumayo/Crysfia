
#include "LayerIsland.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include "../Live2d/LAppView.h"

#include <vector>
#include <functional>

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    void LayerIslandMark::pasteMap( cocos2d::Sprite * map, CityPointData const & data )
    {
        initData( data );

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
        auto pixel = map->getContentSize( ) / scale;

        map->addChild( this );

        setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
        setScale( Lib::fitWidth( this, 128 * scale ), Lib::fitWidth( this, 128 * scale ) );

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

        LayerIslandMark::pasteMap( map, data );
    }

    IslandMap * IslandMap::make( )
    {
        const std::string dir = u8"res/texture/system/";

        initWithFile( dir + u8"worldmap.png" );

        setAnchorPoint( Vec2( 0, 0 ) );
        setScale( 2 );
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

        IslandMap::Islands island = ( IslandMap::Islands )UserDefault::getInstance( )->getIntegerForKey( u8"ëÿç›íÜÇÃìá" );

        std::vector<int> days =
        {
            1, 8, 7, 9, 5, 1
        };
        std::vector<CityPointData> point =
        {
            { Vec2( 100, 100 ), u8"island.json" },
            { Vec2( 206, 510 ), u8"island.json" },
            { Vec2( 314, 374 ), u8"island.json" },
            { Vec2( 567, 482 ), u8"island.json" },
            { Vec2( 618, 366 ), u8"island.json" },
            { Vec2( 803, 582 ), u8"island.json" },
        };

        int sum = 0;
        for ( int i = 0; i < island; ++i ) sum += days[i];
        auto day = UserDefault::getInstance( )->getIntegerForKey( u8"ì˙" );
        if ( day < sum )
        {
            scheduleOnce( [ = ] ( float d ) {SceneManager::createCityMap( point[island].path ); }, 0.016F, std::string( u8"scene" ) );

            return true;
        }

        auto background = IslandMap::create( )->make( );
        this->addChild( background );



        for ( int i = 1; i < 6; ++i )
        {
            CityMark::create( )->pasteMap( background, point[i] );
        }


        if ( island != IslandMap::Islands::fifth )
        {
            movePoint( background, point[island].position, point[island + 1].position, point[island].path );
        }

        return true;
    }
    void LayerIsland::setup( )
    {

    }
    void User::LayerIsland::movePoint( cocos2d::Sprite* map, cocos2d::Vec2 start, cocos2d::Vec2 end, std::string path )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto sprite = Sprite::create( u8"res/texture/system/kuroeicon.png" );
        map->addChild( sprite );
        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );
        auto pixel = map->getContentSize( ) / scale;
        sprite->setPosition( Vec2( start.x, pixel.height - start.y ) * scale );
        sprite->setScale( Lib::fitWidth( this, 128 * scale ), Lib::fitWidth( this, 128 * scale ) );
        map->setPosition( vo + vs * 0.5 - Vec2( start.x, pixel.height - start.y ) * scale * map->getScale( ) );
        map->runAction( MoveTo::create( 5.0F, vo + vs * 0.5 - Vec2( end.x, pixel.height - end.y ) * scale * map->getScale( ) ) );

        sprite->setRotation( -30 );
        auto huriko = Sequence::create( RotateTo::create( 0.5, 30 ), RotateTo::create( 0.5, -30 ), nullptr );
        auto hurikoendless = RepeatForever::create( huriko );
        auto move = Sequence::create( MoveTo::create( 5.0F, Vec2( end.x, pixel.height - end.y ) * scale ), CallFunc::create( [ path ]
        {
            auto value = UserDefault::getInstance( )->getIntegerForKey( u8"ëÿç›íÜÇÃìá" );
            UserDefault::getInstance( )->setIntegerForKey( u8"ëÿç›íÜÇÃìá", value + 1 );
            SceneManager::createCityMap( path );
        } ), nullptr );

        sprite->runAction( hurikoendless );
        sprite->runAction( move );
    }
}
