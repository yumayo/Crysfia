#include "Home.h"
#include "FrameLayer.h"
#include "UIManager.h"
#include "BGManager.h"
USING_NS_CC;

namespace User
{
	cocos2d::Scene * Home::create()
	{
		auto scene = Scene::create();

		scene->addChild(createLayer<UIManager>(),UI);
		scene->addChild(createLayer<BGManager>(), BACKGROUND);

		return scene;
	}
}