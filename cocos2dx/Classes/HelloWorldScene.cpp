#include "HelloWorldScene.h"
#include "User/SceneManager.h"

USING_NS_CC;

cocos2d::Scene* HelloWorldScene::createScene( )
{
    return User::SceneManager::createTitle( );
}
