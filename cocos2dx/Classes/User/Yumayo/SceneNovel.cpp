#include "SceneNovel.h"

#include "TextTypes.hpp"

#include "NameLayer.h"
#include "HumanLayer.h"
#include "NovelLayer.h"
#include "SystemLayer.h"
#include "BackgroundLayer.h"
#include "SelectLayer.h"
#include "StillLayer.h"

#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneNovel::create( std::string const& novelPath )
    {
        ScriptStaticData::setup( );

        auto scene = Scene::create( );
        scene->addChild( createLayer<SystemLayer>( ), (int)Tag::System );
        scene->addChild( createLayer<BackgroundLayer>( ), (int)Tag::Background );
        scene->addChild( createLayer<StillLayer>( ), (int)Tag::Still );
        scene->addChild( createLayer<HumanLayer>( ), (int)Tag::Human );
        scene->addChild( createLayer<NovelLayer>( novelPath ), (int)Tag::Novel );
        scene->addChild( createLayer<NameLayer>( ), (int)Tag::Name );
        scene->addChild( createLayer<SelectLayer>( ), (int)Tag::Select );
        return scene;
    }
}
