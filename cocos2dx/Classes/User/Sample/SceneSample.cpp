#include "SceneSample.h"

#include "Water.h"
#include "Fia.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneSample::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<Water>( ) );
        scene->addChild( createLayer<Fia>( ) );
        return scene;
    }
}
