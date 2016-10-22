#include "SceneYumayo.h"

#include "ScriptTestLayer.h"
#include "NameLayer.h"
#include "HumanLayer.h"

#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneYumayo::create( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<HumanLayer>( ), 2000 );
        scene->addChild( createLayer<NameLayer>( ), 1000 );
        scene->addChild( createLayer<ScriptTestLayer>( ), 0 );
        ScriptStaticData scriptStaticData( scene );
        return scene;
    }
}
