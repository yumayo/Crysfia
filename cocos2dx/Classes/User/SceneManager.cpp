#include "SceneManager.h"
#include "LayerBase.h"

// scenario�Ɏg����ϐ��̃T�C�Y�Ȃǂ̏������B
#include "Yumayo/OptionalValues.h"

// �T���v���V�[�����쐬���܂��B
#include "Sample/SceneSample.h"

// ���[�}���̃m�x���V�[�����쐬���܂��B
#include "Yumayo/SceneNovel.h"

// ���}�b�v�V�[�����쐬���܂��B
#include "IslandMap/SceneIslandMap.h"

// �X�}�b�v�V�[�����쐬���܂��B
#include "CiryMap/SceneCityMap.h"

// ��������̃z�[���V�[�����쐬���܂��B
#include "Breeding/SceneBreeding.h"
#include "Breeding/SceneCreaning.h"
#include "Breeding/SceneCloset.h"

// ��������̃^�C�g���V�[����ǉ����܂��B
#include "Title/SceneTitle.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        OptionalValues::setup( );

		createBreeding();
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
	void SceneManager::createCreaning()
	{
		create<SceneCreaning>();
	}

	void SceneManager::createCloset()
	{
		create<SceneCloset>();
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
