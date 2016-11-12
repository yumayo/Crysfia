#include "SceneBreeding.h"
#include "UIManager.h"
#include "BGManager.h"
#include "Test.h"
USING_NS_CC;

namespace User
{
	cocos2d::Scene * SceneBreeding::create()
	{
		auto scene = Scene::create();

		scene->addChild(createLayer<UIManager>(),UI);
		//scene->addChild(createLayer<BGManager>());
		//scene->addChild(createLayer<Test>(), BACKGROUND);
		return scene;
	}
}