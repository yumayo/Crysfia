#include "SceneNovel.h"

#include "TextTypes.hpp"

#include "NameLayer.h"
#include "HumanLayer.h"
#include "NovelLayer.h"
#include "SystemLayer.h"
#include "BackgroundLayer.h"
#include "SelectLayer.h"
#include "StillLayer.h"
#include "BackLogLayer.h"
#include "HeartLayer.h"
#include "Live2dLayer.h"
#include "FlickFunctionLayer.h"
#include "ItemLayer.h"

#include "ScriptSystem.h"

#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene * SceneNovel::create( std::string const& novelPath )
    {
        auto scene = Scene::create( );

        scene->addChild( createLayer<BackgroundLayer>( ), (int)Tag::Background );
        scene->addChild( createLayer<StillLayer>( ), (int)Tag::Still );
        scene->addChild( createLayer<HumanLayer>( ), (int)Tag::Human );
        scene->addChild( createLayer<Live2dLayer>( ), (int)Tag::Live2d );
        scene->addChild( createLayer<NovelLayer>( novelPath ), (int)Tag::Novel );
        scene->addChild( createLayer<NameLayer>( ), (int)Tag::Name );
        scene->addChild( createLayer<HeartLayer>( ), (int)Tag::Heart );
        scene->addChild( createLayer<SelectLayer>( ), (int)Tag::Select );
        scene->addChild( createLayer<ItemLayer>( ), (int)Tag::ItemLayer );
        scene->addChild( createLayer<FlickFunctionLayer>( ), (int)Tag::FlickFunction );
        scene->addChild( createLayer<BackLogLayer>( ), (int)Tag::BackLog );

        // システムレイヤーの登録
        // 全てのスクリプトを司る"sys"は初期化の時点で登録をします。
        auto system = createLayer<SystemLayer>( );
        scene->addChild( system, (int)Tag::System );
        auto script = new ScriptSystem( system );
        script->setup( );
        REGIST_VARIABLE( u8"sys", script );

        return scene;
    }
}
