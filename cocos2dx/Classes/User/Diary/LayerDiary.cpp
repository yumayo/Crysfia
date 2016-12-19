#include "LayerDiary.h"

#include "../SceneManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;

namespace User
{
	LayerDiary::LayerDiary()
	{

	}
	LayerDiary::~LayerDiary()
	{

	}

	bool LayerDiary::init() {
		if (!Layer::init()) {
			return false;
		}

		// 画面サイズを取得
		Size winSize = Director::getInstance()->getVisibleSize();

		// バックグランドカラー
		auto background = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);

		// バックグランドカラー第2引数は表示順
		this->addChild(background, 0);

		// リストビューの作成
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleSize();

		listView = cocos2d::ui::ListView::create();
		listView->setContentSize(Size(700, 800));
		listView->setPosition((visibleSize - listView->getContentSize()) / 2);
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setBounceEnabled(true);
		listView->setTag(0);
		this->addChild(listView);

		// ボタンのタグを調整する変数
		tag = 0;
		/*int num = 1;*/

		// ボタンの生成
		for (int i = 1; i < 6; ++i) {
			
			auto node = ui::Layout::create();
			node->setTag(i);

			auto button01 = ui::Button::create("res/Image/WindowBase/WinBase_8.png", "res/Image/WindowBase/WinBase_9.png");
			node->addChild(button01);
			button01->setTag(i + tag);
			//button01->setName(StringUtils::format("button%d", i + tag));
			button01->setPosition(Vec2(150, 100));
			button01->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

			tag += 1;

			auto button02 = ui::Button::create("res/Image/WindowBase/WinBase_8.png", "res/Image/WindowBase/WinBase_9.png");
			node->addChild(button02);
			button02->setTag(i + tag);
			//button02->setName(StringUtils::format("button%d", i + tag));
			button02->setPosition(Vec2(350, 100));
			button02->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

			tag += 1;

			auto button03 = ui::Button::create("res/Image/WindowBase/WinBase_8.png", "res/Image/WindowBase/WinBase_9.png");
			node->addChild(button03);
			button03->setTag(i + tag);
			//button03->setName(StringUtils::format("button%d", i + tag));
			button03->setPosition(Vec2(550, 100));
			button03->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

			node->setContentSize(Size(visibleSize.width, button01->getContentSize().height + 100));

			listView->addChild(node);
		}

		// 日記を開いているかどうか
		flagDiary = false;

		{
			auto scale = Director::getInstance()->getContentScaleFactor();

			auto button = ui::Button::create(u8"res/texture/system/backbutton.png");
			addChild(button);
			button->setScale(0.5, 0.5);
			button->setAnchorPoint(Vec2(0, 0));
			button->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					SceneManager::createBreeding();
				}
			});
		}

		return true;
	}

	// ボタンをタッチしたときの反応
	void LayerDiary::touchEvent(Ref *pSender, ui::Widget::TouchEventType type) {

		if (type == ui::Widget::TouchEventType::BEGAN) {
			auto button = ui::Button::create("res/Image/WindowBase/WinBase_8.png");
			auto leftButton = ui::Button::create("res/texture/left-button.png");
			auto rightButton = ui::Button::create("res/texture/left-button.png");
			auto l = getChildByTag(0);
			auto n = l->getChildByTag(1);
			//auto c = n->getChildByName("button1");

			// ↓ここの数字を変えれば何番目の画像を出すか変えられる
			auto c = n->getChildByTag(1);
			auto t = c->getTag();

			if (pSender == c) {
				selectDiary(t);

			}
			
			

			if (!flagDiary) {

				button->setPosition(Vec2(150, 100));
				button->setTitleText("return");
				button->setTitleFontSize(60);
				this->addChild(button);

				leftButton->setPosition(Vec2(350, 100));
				leftButton->setScale(0.1);
				this->addChild(leftButton);
				
				rightButton->setPosition(Vec2(600, 100));
				rightButton->setScale(0.1);
				rightButton->setRotation(180);
				this->addChild(rightButton);

				flagDiary = true;
			}
		}
	}

	// ボタンをタッチされたらこれで画像を描画
	void LayerDiary::selectDiary(int _namu) {
		auto sprite = Sprite::create(StringUtils::format("res/texture/home/miku_%d.png", _namu));
		sprite->setPosition(Vec2(200, 500));
		this->addChild(sprite);

		flagDiary = false;
	}

	/*void LayerDiary::selectDiary(cocos2d::ui::Button *button) {
		int tag = button->getTag();
		auto sprite = Sprite::create(StringUtils::format("res/Image/WindowBase/WinBase_%d.png", tag));
		sprite->setPosition(Vec2(200, 300));
		this->addChild(sprite);

		flagDiary = false;
	}*/


	/*void LayerDiary::selectDiary(int num) {
		auto sprite = Sprite::create(StringUtils::format("res/Image/WindowBase/WinBase_%d.png", num));
		sprite->setPosition(Vec2(200, 300));
		this->addChild(sprite);
	}*/

}