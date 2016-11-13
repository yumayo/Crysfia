#include "Test.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

namespace User
{
    Test::Test( )
    {
        
    }
    Test::~Test( )
    {
        
    }
	bool Test::init()
	{
		if (!Layer::init()) { return false; }

		auto winSize = Director::getInstance()->getVisibleSize();

		auto sprite = Sprite::create("HelloWorld.png");
		sprite->setPosition(Vec2::ZERO);
		addChild(sprite);

		auto background = LayerColor::create(Color4B::GRAY, winSize.width, winSize.height);
		addChild(background);


		return true;
	}
}
