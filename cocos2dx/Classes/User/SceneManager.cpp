#include "SceneManager.h"
#include "LayerBase.h"

// サンプルシーンを作成します。
#include "Sample/SceneSample.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        createSample( );
    }
    void SceneManager::createSample( )
    {
        SceneSample sample;
        auto scene = sample.create( );

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
        }
    }
}
