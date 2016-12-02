#include "SceneYumayo.h"

#include "ScriptTestLayer.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneYumayo::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<ScriptTestLayer>( ) );
        return scene;
    }
}
