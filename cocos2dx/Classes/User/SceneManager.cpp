#include "SceneManager.h"
#include "LayerBase.h"

// �T���v���V�[�����쐬���܂��B
#include "Sample/SceneSample.h"

// ���[�}���V�[�����쐬���܂��B
#include "Yumayo/SceneYumayo.h"

#include "Yumayo/OptionalValues.h"

// ���}�b�v�V�[�����쐬���܂��B
#include "IslandMap/SceneIslandMap.h"

// ��������̃V�[�����쐬���܂��B
#include "Breeding/Home.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        OptionalValues::setup( );

        createIslandMap( );
    }
    void SceneManager::createSample( )
    {
        SceneSample base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        Director::getInstance( )->replaceScene( scene );
    }
    void SceneManager::createYumayo( )
    {
        SceneYumayo base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        Director::getInstance( )->replaceScene( scene );
    }
    void SceneManager::createIslandMap( )
    {
        SceneIslandMap base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        Director::getInstance( )->replaceScene( scene );
    }
    void SceneManager::createBreeding( )
    {
        Home base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        Director::getInstance( )->replaceScene( scene );
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
