
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
    LayerIsland::LayerIsland( )
    {
    }
    LayerIsland::~LayerIsland( )
    {
    }
    bool LayerIsland::init( )
    {
        if ( !Layer::init( ) ) return false;

        Islands staying_island = (Islands)UserDefault::getInstance( )->getIntegerForKey( u8"滞在中の島" );

        std::vector<int> days =
        {
            0, 8, 4, 1
        };
        std::vector<std::string> point =
        {
            u8"無名の島",
            u8"ラシャス島",
            u8"ヒャルキシ島",
            u8"アイクラ島",
        };

        int sum = 0;
        for ( int i = Islands::none; i <= staying_island; ++i ) sum += days[i];
        auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        if ( day <= sum )
        {
            /* nothing */
        }
        else if ( staying_island < Islands::aikura )
        {
            staying_island = Islands( staying_island + 1 );
            UserDefault::getInstance( )->setIntegerForKey( u8"滞在中の島", staying_island );
        }

        scheduleOnce( [ = ] ( float d ) { SceneManager::createCityMap( point[staying_island] ); }, 0.0F, std::string( u8"scene.island" ) );

        return true;
    }
    void LayerIsland::setup( )
    {

    }
}
