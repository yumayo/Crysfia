#include "SceneSample.h"

#include "LayerWater.h"
#include "LayerFia.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneSample::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<LayerWater>( ) );
        scene->addChild( createLayer<LayerFia>( ) );
        return scene;
    }
}
