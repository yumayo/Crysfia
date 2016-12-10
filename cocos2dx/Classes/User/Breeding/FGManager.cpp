#include "FGManager.h"

USING_NS_CC;

namespace User
{
    FGManager::FGManager( ):
		winSize(Director::getInstance()->getVisibleSize())
    {
		auto foreground = LayerColor::create(Color4B(0,0,0,0));
		this->addChild(foreground);
    }

    FGManager::~FGManager( )
    {
        
    }

	bool FGManager::init()
	{
		if (!Layer::init()) { return false; }



		return true;
	}

}
