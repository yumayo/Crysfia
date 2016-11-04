#include "BGManager.h"
USING_NS_CC;

namespace User
{
	bool BGManager::init()
	{

		auto size = Director::getInstance()->getVisibleSize();
		auto background = Sprite::create("res/texture/背景市場.png");
		background->setPosition(size/2);
		background->setScale(0.65);
		this->addChild(background);
		
		return true;
	}
}
