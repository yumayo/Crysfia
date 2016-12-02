#include "LayerCleaning.h"
#include "SceneBreeding.h"
USING_NS_CC;

namespace User
{
	LayerCleaning::LayerCleaning() :
		winSize(Director::getInstance()->getVisibleSize()),
		bottle(Sprite::create("res/texture/home/bottle_1.png")),
		mask(Sprite::create()),
		clippingNode(ClippingNode::create()),
		clippingShape(Sprite::create("res/texture/home/bottle_mask.png"))
	{
		bottle->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		bottle->setScale(0.5f);
		this->addChild(bottle, 10);

		mask->setTextureRect(Rect(0, 0, winSize.width - 50, winSize.height - 350));
		mask->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.38f));
		mask->setColor(Color3B::BLACK);
		mask->setOpacity(128);

		clippingShape->setScale(0.5f);
		clippingShape->setPosition(winSize / 2);
		clippingNode->setStencil(clippingShape);
		clippingNode->setInverted(false);
		clippingNode->setAlphaThreshold(0.0f);

		clippingNode->addChild(mask, 20);
		this->addChild(clippingNode, 20);

		buttons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_101.png"));
		buttons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_107.png"));

		buttons[0]->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.05f));
		buttons[1]->setPosition(Vec2(winSize.width * 0.9f, winSize.height * 0.05f));

		for (int i = 0; i < 2; i++) 
		{
			buttons[i]->setScale(0.7f);
			this->addChild(buttons[i], 30);
		}

	}

	LayerCleaning::~LayerCleaning()
	{

	}

	bool LayerCleaning::init()
	{
		if (!Layer::init()) { return false; }

		thisLocationTouchProcess();
		uiTouchProcess();		
		return true;
	}

	void LayerCleaning::thisLocationTouchProcess()
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			return true;
		};

		//スワイプ処理
		listener->onTouchMoved = [=](Touch* touch, Event* event) {

			//ビンとタッチした場所のあたり判定をとるためタッチした位置を取得
			auto location = touch->getLocation();

			//１フレーム前のタッチ位置との差分を取得
			auto delta = touch->getDelta();

			//差分X、Yを足した値の絶対値をとりその値を５０分の１にした値にに制限をかける。
			//この値を使ってマスクの透過度から引いていく
			int creanVal = clampf((abs(delta.x + delta.y) * 0.05), 0, 2);

			//ざっくりとしたあたり判定に使うための矩形
			auto rect = Rect(mask->getPosition().x - mask->getContentSize().width / 2,
				mask->getPosition().y - mask->getContentSize().width / 2,
				mask->getContentSize().width,
				mask->getContentSize().height);

			if (5 < mask->getOpacity())
			{
				if (rect.containsPoint(location))
				{
					mask->setOpacity(mask->getOpacity() - creanVal);
					log("%d", mask->getOpacity());
				}
			}
			else if (mask->getOpacity() >= 0 && mask->getOpacity() <= 5)
			{
				  mask->setOpacity(0); 
			}
		};

		listener->onTouchEnded = [=](Touch* touch, Event* event) {
			mask->stopAllActions();
		};

		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}

	//掃除レイヤー内でのUI処理
	void LayerCleaning::uiTouchProcess()
	{
		//戻るボタン
		buttons[0]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				
			}
		});
	}

	void LayerCleaning::hoge()
	{
		auto currentScene = (Scene*)Director::getInstance()->getRunningScene();
		currentScene->removeAllChildren();
	}
}
