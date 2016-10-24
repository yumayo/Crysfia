#include "SceneYumayo.h"

#include "TextTypes.hpp"

#include "NameLayer.h"
#include "HumanLayer.h"
#include "NovelLayer.h"
#include "SystemLayer.h"
#include "BackgroundLayer.h"

#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneYumayo::create( )
    {
        auto scene = Scene::create( );
        OptionalValues::setup( );
        scene->addChild( createLayer<SystemLayer>( ), (int)Tag::System );
        scene->addChild( createLayer<BackgroundLayer>( ), (int)Tag::Background );
        scene->addChild( createLayer<HumanLayer>( ), (int)Tag::Human );
        scene->addChild( createLayer<NameLayer>( ), (int)Tag::Name );
        scene->addChild( createLayer<NovelLayer>( ), (int)Tag::Novel );
        return scene;
    }
}
