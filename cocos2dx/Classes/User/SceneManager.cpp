#include "SceneManager.h"
#include "LayerBase.h"

// scenario�Ɏg����ϐ��̃T�C�Y�Ȃǂ̏������B
#include "Novel/OptionalValues.h"

// ���[�}�����Ǘ�����V�[�����쐬���܂��B
#include "Novel/SceneNovel.h"
#include "IslandMap/SceneIslandMap.h"
#include "CiryMap/SceneCityMap.h"

// �������񂪊Ǘ�����V�[�����쐬���܂��B
#include "Breeding/SceneBreeding.h"
#include "Title/SceneTitle.h"

// �΋����񂪊Ǘ�����V�[�����쐬���܂��B
#include "Ishibashi/Scene_ishibashi.h"

// ���R���񂪊Ǘ�����V�[�����쐬���܂��B
#include "Diary/SceneDiary.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        OptionalValues::setup( );
        createIslandMap( );
    }
    void SceneManager::createTitle( )
    {
        create<SceneTitle>( );
    }
    void SceneManager::createNovel( std::string const& novelPath )
    {
        create<SceneNovel>( novelPath );
    }
    void SceneManager::createIslandMap( )
    {
        create<SceneIslandMap>( );
    }
    void SceneManager::createCityMap( std::string const& backgroundPath )
    {
        create<SceneCityMap>( backgroundPath );
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
