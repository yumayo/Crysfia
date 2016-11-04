#include "Test.h"

USING_NS_CC;

namespace User
{
    Test::Test( )
    {
        
    }
	bool Test::init()
	{
		if (!ui::Button::init()) { return false; }
		
		auto winSize = Director::getInstance()->getWinSize();
		auto button = ui::Button::create("option_icon.png");
		button->setPosition(Vec2(winSize/2));
		button->setScale(0.5);
		addChild(button);

		return true;
	}
}
