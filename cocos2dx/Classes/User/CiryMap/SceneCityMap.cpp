#include "SceneCityMap.h"

#include "LayerCity.h"

#include "../Novel/HeartLayer.h"

#include "../Novel/SystemLayer.h"
#include "../Novel/ScriptSystem.h"
#include "../Novel/ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* SceneCityMap::create( std::string const & backgroundPath )
    {
        auto scene = Scene::create( );

        scene->addChild( createLayer<HeartLayer>( ), (int)Tag::Heart );

        // システムレイヤーの登録
        // 全てのスクリプトを司る"sys"は初期化の時点で登録をします。
        auto system = createLayer<SystemLayer>( );
        scene->addChild( system, (int)Tag::System );
        auto script = new ScriptSystem( system );
        script->setup( );
        REGIST_VARIABLE( u8"sys", script );

        auto data = UserDefault::getInstance( );
        auto 好感度 = data->getFloatForKey( u8"好感度" );
        好感度 += 0.1;
        data->setFloatForKey( u8"好感度", 好感度 );

        scene->addChild( createLayer<LayerCity>( backgroundPath ) );

        return scene;
    }
}
