#include "SceneCloset.h"

USING_NS_CC;

namespace User
{
    SceneCloset::SceneCloset( )
    {
        
    }
    SceneCloset::~SceneCloset( )
    {
        
    }
	cocos2d::Scene * SceneCloset::create()
	{
		auto scene = Scene::create();
		return scene;
	}
}
