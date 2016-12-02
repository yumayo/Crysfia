#include "SceneBreeding.h"
#include "UIManager.h"
#include "BGManager.h"
#include "FGManager.h"
#include "TemporaryCharacter.h"
#include "LayerCleaning.h"
#include "VariousStatus.h"
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

		scene->addChild(createLayer<BGManager>(), (int)zOder::BACKGROUND, (int)tabLayer::BACKGROUND);
		scene->addChild(createLayer<TemporaryCharacter>(), (int)zOder::CHARACTER, (int)tabLayer::CHARACTER);
		scene->addChild(createLayer<UIManager>(), (int)zOder::UI_MANAGER, (int)tabLayer::UI_MANAGER);
		scene->addChild(createLayer<FGManager>(), (int)zOder::FOREGROUND, (int)tabLayer::FOREGROUND);
		scene->addChild(createLayer<LayerManager>(), 0,4);

		return scene;
	}

}