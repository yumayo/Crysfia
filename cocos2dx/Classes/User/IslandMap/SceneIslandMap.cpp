#include "SceneIslandMap.h"

#include "LayerIsland.h"
USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneIslandMap::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<LayerIsland>( ) );

        return scene;
    }
}
