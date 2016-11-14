#include "SceneDiary.h"

USING_NS_CC;

namespace User
{
	SceneDiary::SceneDiary()
	{

	}
	SceneDiary::~SceneDiary()
	{

	}
	cocos2d::Scene * SceneDiary::create()
	{
		auto scene = Scene::create();

		scene->addChild(createLayer<LayerDiary>());
		return scene;
	}
}
