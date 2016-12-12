#include "LayerCleaning.h"
#include "SceneBreeding.h"
#include "LayerManager.h"
USING_NS_CC;

namespace User
{
	LayerCleaning::LayerCleaning() :
		winSize(Director::getInstance()->getVisibleSize()),
		bottle(Sprite::create("res/texture/home/bottle_1.png")),
		mask(Sprite::create()),
		clippingNode(ClippingNode::create()),
		clippingShape(Sprite::create("res/texture/home/bottle_mask.png")),
		canCleaning(false),
		listener(EventListenerTouchOneByOne::create())
	{
		

		infoLabel = cleanDegrees != 0 ? Label::createWithTTF(TTFConfig("res/fonts/meiryo.ttc", 36), u8"画面をタップで\n お掃除開始！") :
			Label::createWithTTF(TTFConfig("res/fonts/meiryo.ttc", 36), u8"きれいだよ(=ﾟωﾟ)ﾉ");

		bottle->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		bottle->setScale(0.5f);
		this->addChild(bottle, 10);

		mask->setTextureRect(Rect(0, 0, winSize.width - 50, winSize.height - 350));
		mask->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.38f));
		mask->setColor(Color3B::BLACK);
		mask->setOpacity(cleanDegrees);

		clippingShape->setScale(0.5f);
		clippingShape->setPosition(winSize / 2);
		clippingNode->setStencil(clippingShape);
		clippingNode->setInverted(false);
		clippingNode->setAlphaThreshold(0.0f);

		clippingNode->addChild(mask, 20);
		this->addChild(clippingNode, 20);

		buttons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_101.png"));
		buttons[0]->setScale(0.7f);
		buttons[0]->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.05f));
		this->addChild(buttons[0], 30);

		listener->setSwallowTouches(true);
	}

	LayerCleaning::~LayerCleaning()
	{

	}

	bool LayerCleaning::init()
	{
		if (!Layer::init()) { return false; }

		//UserDefaultで値を取り出したりセットしたりする
		UserDefault* _userDef = UserDefault::getInstance();
		_userDef->setIntegerForKey("aaa", 100);
		auto hoge = _userDef->getIntegerForKey("aaa");
		log(u8"日にち=[%d]", hoge);

		auto background = Sprite::create("res/texture/home/cleaning_bg.jpg");
		background->setPosition(winSize / 2);
		background->setScale(4.f);
		this->addChild(background);

		uiTouchProcess();
		setInfoLayer();

		listener->onTouchBegan = [=](Touch* touch, Event* event) { return true; };
		listener->onTouchEnded = [this](Touch* touch, Event* event) {
			if (cleanDegrees != 0)canCleaning = true;
			if (canCleaning)
			{
				thisLocationTouchProcess();
				this->removeChildByTag(1);
			}
		};

		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	void LayerCleaning::thisLocationTouchProcess()
	{
		
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			//ビンとタッチした場所のあたり判定をとるためタッチした位置を取得
			touchLocation = touch->getLocation();
			return true;
		};

		//スワイプ処理
		listener->onTouchMoved = [this](Touch* touch, Event* event) {

			//１フレーム前のタッチ位置との差分を取得
			auto delta = touch->getDelta();

			//差分X、Yを足した値の絶対値をとりその値を５０分の１にした値にに制限をかける。
			//この値を使ってマスクの透過度から引いていく
			int creanVal = clampf((abs(delta.x + delta.y) * 0.05), 0, 2);

			//ざっくりとしたあたり判定に使うための矩形を用意
			auto rect = Rect(mask->getPosition().x - mask->getContentSize().width / 2,
				mask->getPosition().y - mask->getContentSize().width / 2,
				mask->getContentSize().width,
				mask->getContentSize().height);

			if (5 < mask->getOpacity())
			{
				if (rect.containsPoint(touchLocation))
				{
					mask->setOpacity(mask->getOpacity() - creanVal);
				}
			}
			else if (mask->getOpacity() >= 0 && mask->getOpacity() <= 5)
			{
				mask->setOpacity(0);
				//TODO: 掃除完了の演出を入れる
				UserDefault::getInstance()->setIntegerForKey(u8"汚れ度", 0);
				if (!isFinish)
				{
					completeDirection();
					isFinish = true;
				}
			}

		};

		listener->onTouchEnded = [=](Touch* touch, Event* event) {
			mask->stopAllActions();
		};

	}

	//掃除レイヤー内でのUI処理
	void LayerCleaning::uiTouchProcess()
	{
		//メニュー画面へ戻る
		buttons[0]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				auto p = (LayerManager*)this->getParent();
				p->changeToSubMenuLayer();
			}
		});
	}

	void LayerCleaning::setInfoLayer()
	{
		auto layer = Layer::create();
		infoLabel->setPosition(winSize / 2);
		infoLabel->setColor(Color3B::WHITE);
		infoLabel->enableShadow(Color4B::BLACK);
		layer->addChild(infoLabel);
		this->addChild(layer, 40, 1);
		this->schedule(schedule_selector(LayerCleaning::labelAction), 3);
	}

	void LayerCleaning::setInfoLayer(cocos2d::Node* _node, cocos2d::Label* _label, std::string _text, int _fontSize)
	{
		_label = Label::createWithTTF(TTFConfig("res/fonts/meiryo.ttc", _fontSize), _text);
		_label->setPosition(winSize / 2);
		_label->setColor(Color3B::WHITE);
		_label->enableShadow(Color4B::BLACK);
		_node->addChild(_label, 40);
	}

	void LayerCleaning::labelAction(float dt)
	{
		//ジャンプアクションの設定
		//引数: 1.時間 2.座標 3.高さ 4.回数
		for (int i = 0; i < infoLabel->getStringLength(); i++) {
			auto oneChracter = infoLabel->getLetter(i);
			if (oneChracter) {
				auto testAction = Sequence::create(DelayTime::create(1 + i*0.1), JumpBy::create(0.5f, Vec2(0, 0), 10, 1), nullptr);
				oneChracter->runAction(testAction);
			}
		}
	}

	//掃除完了の
	void LayerCleaning::completeDirection()
	{
		auto _layer = Layer::create();
		this->addChild(_layer);
		Label* _label = Label::create();
		setInfoLayer(_layer, _label, u8"じょうずにできました！", 36);
	}

}