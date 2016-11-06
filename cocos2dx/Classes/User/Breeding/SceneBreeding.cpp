#include "SceneBreeding.h"
#include "FrameLayer.h"
#include "UIManager.h"
#include "BGManager.h"
USING_NS_CC;

namespace User
{
	cocos2d::Scene * SceneBreeding::create()
	{
		auto scene = Scene::create();

		scene->addChild(createLayer<UIManager>(),UI);
		scene->addChild(createLayer<BGManager>(), BACKGROUND);

		return scene;
	}
}