#include "SceneManager.h"
#include "LayerBase.h"

// scenarioに使われる変数のサイズなどの初期化。
#include "Yumayo/OptionalValues.h"

// サンプルシーンを作成します。
#include "Sample/SceneSample.h"

// ユーマヨのノベルシーンを作成します。
#include "Yumayo/SceneNovel.h"

// 島マップシーンを作成します。
#include "IslandMap/SceneIslandMap.h"

// 街マップシーンを作成します。
#include "CiryMap/SceneCityMap.h"

// 小松さんのホームシーンを作成します。
#include "Breeding/SceneBreeding.h"

// 小松さんのタイトルシーンを追加します。
#include "Title/SceneTitle.h"

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
    void SceneManager::createSample( )
    {
        create<SceneSample>( );
    }
    void SceneManager::createNovel( std::string const& novelPath )
    {
        create<SceneNovel>( novelPath );
    }
    void SceneManager::createIslandMap( )
    {
        create<SceneIslandMap>( );
    }
    void SceneManager::createCiryMap( std::string const& backgroundPath )
    {
        create<SceneCityMap>( backgroundPath );
    }
    void SceneManager::createBreeding( )
    {
        create<SceneBreeding>( );
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
