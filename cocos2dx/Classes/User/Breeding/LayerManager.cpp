#include "LayerManager.h"
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

		auto s = Sprite::create("res/Image/WindowBase/WinBase_88.png");
		s->setPosition(Director::getInstance()->getVisibleSize()/2);
		s->setScale(0.5f);

		this->addChild(s);

		
		return true;
	}


}
