#include "BGManager.h"
USING_NS_CC;

namespace User
{
	bool BGManager::init()
	{
		auto size = Vec2(720, 1280);
		auto background = Sprite::create("res/Image/bg.jpg");
		background->setPosition(size/2);
		background->setScale(2.6f);
		this->addChild(background);

		return true;
	}
}
