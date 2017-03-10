#include "SceneTitle.h"
#include "TitleManager.h"
USING_NS_CC;

namespace User
{
	cocos2d::Scene * User::SceneTitle::create()
	{
		auto scene = Scene::create();

		scene->addChild(createLayer<TitleManager>());

		return scene;
	}
}
