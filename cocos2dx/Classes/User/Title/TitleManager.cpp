#include "TitleManager.h"
#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
	TitleManager::TitleManager():
		uiLabel(Label::createWithSystemFont("TAP TO SCREEN", "Arial", 40)),
		fadeSprite(nullptr)
	{
	}
	TitleManager::~TitleManager() {}

	bool TitleManager::init()
	{
		if (!Layer::init()) { return false; }
		
		createTitleWindow();
		createTapUI();
		createFadeSprite();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [&](Touch* touch, Event* event) {
			return true;
		};

		listener->onTouchEnded = [&](Touch* touch, Event* event) {
			uiLabel->runAction(afterAction());
			fadeSprite->runAction(fadeAction(2,1));
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	}

	void TitleManager::createTitleWindow()
	{
		auto winSize = Director::getInstance()->getVisibleSize();

		auto backGround = Sprite::create("res/texture/背景娯楽の島.png");
		backGround->setPosition(winSize / 2);
		this->addChild(backGround);

		auto titleLabel = Label::createWithSystemFont("Crysfia", "Arial", 150);
		titleLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.7f));
		titleLabel->setColor(Color3B::WHITE);
		titleLabel->enableShadow(Color4B::BLACK);
		this->addChild(titleLabel);
	}

	//"TAP TO SCREEN"(仮)のUIを描画
	void TitleManager::createTapUI()
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		uiLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.55f));
		uiLabel->enableShadow(Color4B::BLACK, Size(4,-4));
		this->addChild(uiLabel);
		uiLabel->runAction(normalAction());
	}

	//フェード演出用の黒い画像。初めは透明度を０に設定。
	void TitleManager::createFadeSprite()
	{
		auto winSize = Director::getInstance()->getVisibleSize();

		fadeSprite = Sprite::create();
		fadeSprite->setTextureRect(Rect(0,0,winSize.width, winSize.height));
		fadeSprite->setColor(Color3B::BLACK);
		fadeSprite->setOpacity(0);
		fadeSprite->setPosition(winSize/2);
		this->addChild(fadeSprite);
	}

	//タップする前のアクション
	cocos2d::Action * TitleManager::normalAction()
	{
		auto fadeIn = FadeIn::create(1);
		auto fadeOut = FadeOut::create(1);
		auto fadeInOut = Sequence::create(fadeOut, fadeIn, nullptr);
		auto fadeRepeat = RepeatForever::create(fadeInOut);
		return fadeRepeat;
	}

	//タップした後のアクション
	cocos2d::Action * TitleManager::afterAction()
	{
		auto fadeIn = FadeIn::create(0.1f);
		auto fadeOut = FadeOut::create(0.1f);
		auto fadeInOut = Sequence::create(fadeOut, fadeIn, nullptr);
		auto fadeRepeat = RepeatForever::create(fadeInOut);
		return fadeRepeat;
	}

	/**********************次のシーンへ移動**********************
		_fadeTime	フェードする時間
		_delayTime	ボタンを押してからフェードが開始するまでの時間
	***********************************************************/
	cocos2d::Action * TitleManager::fadeAction(float _fadeTime, float _delayTime)
	{
		auto fadeIn = FadeIn::create(_fadeTime);
		auto delay = Sequence::create(DelayTime::create(_delayTime), fadeIn, nullptr);
		auto sceneChange = Sequence::create(delay, CallFunc::create([this] {SceneManager::createBreeding(); }), nullptr);
		return sceneChange;
	}
}