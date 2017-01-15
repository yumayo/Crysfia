#include "LayerManager.h"
#include "UIManager.h"
#include "BGManager.h"
#include "FGManager.h"
#include "TemporaryCharacter.h"
#include "LayerCleaning.h"
#include "VariousStatus.h"
#include "../Novel/ScriptHeart.h"
USING_NS_CC;

namespace User
{
	LayerManager::LayerManager()
	{
	
	}

	LayerManager::~LayerManager()
	{

	}

	bool LayerManager::init()
	{
		if (!Layer::init()) { return false; }

		initLayer();
		
		return true;
	}

	void LayerManager::initLayer()
	{
		this->addChild(TemporaryCharacter::create(),	(int)zOder::CHARACTER,	(int)tabLayer::CHARACTER);
		this->addChild(BGManager::create(),				(int)zOder::BACKGROUND, (int)tabLayer::BACKGROUND);
		this->addChild(UIManager::create(),				(int)zOder::UI_MANAGER, (int)tabLayer::UI_MANAGER);
		this->addChild(FGManager::create(),				(int)zOder::FOREGROUND, (int)tabLayer::FOREGROUND);
		
		auto heartGauge = HeartGauge::create()->make();
		heartGauge->setScale(0.85f);
		this->addChild(heartGauge,	(int)zOder::UI_MANAGER, (int)tabLayer::HEARTGAUGE);
	}

	void LayerManager::changeToMainMenuLayer()
	{
	}

	void LayerManager::changeToSubMenuLayer()
	{
		this->addChild(TemporaryCharacter::create(),	(int)zOder::CHARACTER,	(int)tabLayer::CHARACTER);
		this->addChild(UIManager::create(),				(int)zOder::UI_MANAGER, (int)tabLayer::UI_MANAGER);
		this->addChild(BGManager::create(),				(int)zOder::BACKGROUND, (int)tabLayer::BACKGROUND);
		this->removeChildByTag((int)tabLayer::CLEANING);
	}

	void LayerManager::removeLayer()
	{
	}
}
