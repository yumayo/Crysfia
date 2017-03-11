#include "TitleManager.h"
#include "../SceneManager.h"
#include "SceneTitle.h"
#include "../Diary/DiaryDefines.h"
#include "../../Lib/Utilitys.h"
USING_NS_CC;
using namespace experimental;

namespace User
{
	TitleManager::TitleManager() :
		uiLabel(Label::createWithSystemFont("TAP TO SCREEN", FONT_NAME, 50)),
		fadeSprite(nullptr),
		isGameStarted(false),
		isTap(false),
		audioManager(AudioManager::getInstance())
	{
		
	}

	TitleManager::~TitleManager() {}

	bool TitleManager::init()
	{
		if (!Layer::init()) { return false; }

        scheduleOnce( [ this ] ( float delta ) { audioManager->playBgm( "res/sound/BGM/title.mp3" ); }, 0.0F, u8"bgm_delay_TitleManager" );

		createTitleWindow();
		createTapUI();
		createFadeSprite();
		this->scheduleUpdate();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			return true;
		};

		listener->onTouchEnded = [this](Touch* touch, Event* event) {
			isGameStarted = true;
			uiLabel->runAction(afterAction());
			fadeSprite->runAction(fadeAction(1.f, 2.0f));

			if (!isTap) 
			{	
				audioManager->playSe("res/sound/SE/title_se.mp3");
				isTap = true;
			}

		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	}

	void TitleManager::update(float dt)
	{
		if (isGameStarted)
		{
			audioManager->stopBgm(1.0F);
		}
	}

	void TitleManager::createTitleWindow()
	{
		auto winSize = Director::getInstance()->getWinSize();

		auto background = Sprite::create(u8"res/texture/title/background.png");
		background->setPosition(winSize / 2);
		background->setScale( Lib::fitHeight( background, winSize.height ) );
		this->addChild(background);

		auto logo = Sprite::create(u8"res/texture/title/logo_3.png");
		logo->setPosition(Vec2(winSize.width / 2, winSize.height * 0.7f));
		logo->setScale(Lib::fitWidth(background, winSize.width * 1.25f ));
		this->addChild(logo);
	}

	//"TAP TO SCREEN"(仮)のUIを描画
	void TitleManager::createTapUI()
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		uiLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.55f));
		uiLabel->setScale( Lib::fitWidth( uiLabel, winSize.width / 2 ) );
		uiLabel->enableShadow(Color4B::BLACK, Size(4, -4));
		this->addChild(uiLabel);
		uiLabel->runAction(normalAction());
	}

	//フェード演出用の黒い画像。初めは透明度を０に設定。
	void TitleManager::createFadeSprite()
	{
		auto winSize = Director::getInstance()->getVisibleSize();

		fadeSprite = Sprite::create();
		fadeSprite->setTextureRect(Rect(0, 0, winSize.width, winSize.height));
		fadeSprite->setColor(Color3B::BLACK);
		fadeSprite->setOpacity(0);
		fadeSprite->setPosition(winSize / 2);
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
