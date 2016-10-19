#include "SceneManager.h"

#include "Water.h"
#include "Fia.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* SceneManager::createTitle( )
    {
        auto scene = Scene::create( );
        scene->addChild( createLayer<Water>( ) );
        scene->addChild( createLayer<Fia>( ) );

        childrenCallSetup( scene );

        return scene;
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
