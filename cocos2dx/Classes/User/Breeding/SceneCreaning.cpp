#include "SceneCreaning.h"

USING_NS_CC;

namespace User
{
    SceneCreaning::SceneCreaning( )
    {
        
    }
    SceneCreaning::~SceneCreaning( )
    {
        
    }

	cocos2d::Scene * SceneCreaning::create()
	{
		auto scene = Scene::create();
		return scene;
	}
}
