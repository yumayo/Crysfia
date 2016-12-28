#include "SceneCityMap.h"

#include "LayerCity.h"

#include "../../Lib/AudioManager.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* SceneCityMap::create( std::string const & tag )
    {
        auto scene = Scene::create( );

        AudioManager::getInstance( )->readAudioListFile( "res/data/audio.json" );

        scene->addChild( createLayer<LayerCity>( tag ) );

        return scene;
    }
}
