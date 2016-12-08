#include "SceneCityMap.h"

#include "LayerCity.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* SceneCityMap::create( std::string const & tag )
    {
        auto scene = Scene::create( );

        scene->addChild( createLayer<LayerCity>( tag ) );

        return scene;
    }
}
