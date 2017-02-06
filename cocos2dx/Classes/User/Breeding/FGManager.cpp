#include "FGManager.h"

USING_NS_CC;

namespace User
{
    FGManager::FGManager( ):
		winSize(Director::getInstance()->getVisibleSize()),
		mask(Sprite::create("res/texture/novel/mask.png")),
		isFadeIn(true),
		isFadeOut(false)
    {
		mask->setPosition(winSize / 2);
		mask->setScale(0.8f);
    }

    FGManager::~FGManager( )
    {
        
    }

	void FGManager::fading(float _totalTime)
	{
		float intervalTime = _totalTime / 3;
		mask->runAction(Sequence::create( ScaleTo::create(intervalTime, 0),
			DelayTime::create(intervalTime),
			ScaleTo::create(intervalTime,0.8),
			nullptr ));
	}

	
	bool FGManager::init()
	{
		if (!Layer::init()) { return false; }

		auto clipping = ClippingNode::create();
		auto color = LayerColor::create(Color4B::BLACK);
		auto back = Sprite::create("res/texture/home/background_diary.png");
		back->setPosition(winSize/2);
		back->setScale(1.2);
		clipping->addChild(back);
		clipping->setStencil(mask);
		clipping->setInverted(true);
		clipping->setAlphaThreshold(0.0f);		
		addChild(clipping);

		return true;
	}
}