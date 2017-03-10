#include "SceneBreeding.h"
#include "LayerManager.h"

USING_NS_CC;

namespace User
{
	SceneBreeding::SceneBreeding()
	{

	}

	cocos2d::Scene * SceneBreeding::create()
	{
		auto status = UserDefault::getInstance();
		auto dateValue = status->getFloatForKey("day");
		auto dirtyValue = status->getIntegerForKey("dirty");
		status->setIntegerForKey("dirty", dirtyValue + 1);

		auto scene = Scene::create();

		scene->addChild(createLayer<LayerManager>());

		return scene;
	}

}