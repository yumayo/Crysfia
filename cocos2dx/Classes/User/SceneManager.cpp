#include "SceneManager.h"
#include "LayerBase.h"

#include "Novel/OptionalValues.h"

#include "Novel/SceneNovel.h"
#include "CiryMap/SceneCityMap.h"

#include "Breeding/SceneBreeding.h"
#include "Title/SceneTitle.h"

#include "Ishibashi/Scene_ishibashi.h"

#include "SceneManager.h"
#include "LayerBase.h"

#include "Novel/OptionalValues.h"

#include "Novel/SceneNovel.h"
#include "CiryMap/SceneCityMap.h"

#include "Breeding/SceneBreeding.h"
#include "Title/SceneTitle.h"

#include "Ishibashi/Scene_ishibashi.h"

#include "Diary/SceneDiary.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        OptionalValues::setup( );
        createBreeding( );
    }
    void SceneManager::createTitle( )
    {
        create<SceneTitle>( );
    }
    void SceneManager::createNovel( std::string const& scenario, std::function<void( )> const& saveCallFunc )
    {
        create<SceneNovel>( scenario, saveCallFunc );
    }
    void SceneManager::createCityMap( )
    {
        create<SceneCityMap>( );
    }
    void SceneManager::createBreeding( )
    {
        create<SceneBreeding>( );
    }
    void SceneManager::createDiary( )
    {
        create<SceneDiary>( );
    }
    void SceneManager::createIshibashi( )
    {
        create<Scene_ishibashi>( );
    }

    void SceneManager::childrenCallSetup( cocos2d::Scene* scene )
    {
        auto children = scene->getChildren( );
        for ( auto child : children )
        {
            if ( auto childLayer = dynamic_cast<LayerBase*>( child ) )
            {
                childLayer->setup( );
            }
            else
            {
                log( "dynamic_cast is failed : Layer[%s]", child->getName( ).c_str( ) );
            }
        }
    }
}