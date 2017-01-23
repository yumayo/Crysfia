#include "Scene_ishibashi.h"

#include "Layer_ishibashi.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * Scene_ishibashi::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<Layer_meal>( ) );
        return scene;
    }
}