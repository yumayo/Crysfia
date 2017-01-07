#include "TemporaryCharacter.h"

USING_NS_CC;

namespace User
{
    TemporaryCharacter::TemporaryCharacter( ):
		winSize(Director::getInstance()->getVisibleSize()),
		character(Sprite::create("res/texture/home/fia.png")),
		bottle(Sprite::create("res/texture/home/bottle_1.png"))
    {
		character->setPosition(winSize / 2);
		character->setScale(0.3f);
		this->addChild(character);

		bottle->setPosition(Vec2(winSize.width / 2, winSize.height * 0.6));
		bottle->setScale(0.4);
		this->addChild(bottle);
    }

    TemporaryCharacter::~TemporaryCharacter( )
    {
        
    }

	bool TemporaryCharacter::init()
	{
		if (!Layer::init()) { return false; }

		return true;
	}
}
