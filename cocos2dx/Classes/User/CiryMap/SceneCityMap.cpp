#include "SceneCityMap.h"

#include "LayerCity1.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneCityMap::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<LayerCity1>( ) );
        return scene;
    }
}
