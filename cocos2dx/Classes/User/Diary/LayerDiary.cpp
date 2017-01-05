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

		// ボタンの生成
		for (int i = 0; i < 6; ++i)
		{
			auto node = ui::Layout::create();
			node->setTag(i);
			for (int k = 0; k < 3; k++)
			{
				auto button = ui::Button::create("res/Image/WindowBase/WinBase_8.png", "res/Image/WindowBase/WinBase_9.png");
				node->addChild(button);
				button->setTag(i);
				button->setName(StringUtils::format("miku_%d", k));
				button->setPosition(Vec2(150 + k * 200, 100));
				button->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

				node->setContentSize(Size(visibleSize.width, button->getContentSize().height + 100));
			}
			listView->addChild(node);
		}

		// 日記を開いているかどうか
		flagDiary = false;


		// 戻るボタンの生成
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
			for (int i = 0; i < 6; i++)
			{
				auto n = l->getChildByTag(i);
				for (int k = 0; k < 3; k++)
				{
					auto c = n->getChildByTag(k);
					//log("%d", n->getTag());
					//log("%d", c->getTag());
					if (pSender == c) {
						selectDiary(c->getName());
						log("%s", c->getName().c_str());
					}
				}
			}

			if (!flagDiary) {

				button->setPosition(Vec2(150, 100));
				button->setTitleText("return");
				button->setTitleFontSize(60);
				button->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type)
				{
					if (type == ui::Widget::TouchEventType::ENDED)
					{
						SceneManager::createDiary();
					}
				});
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
	void LayerDiary::selectDiary(std::string _name) {

		auto sprite = Sprite::create(StringUtils::format("res/texture/home/%s.png", _name.c_str() ));
		sprite->setPosition(Vec2(200, 500));
		this->addChild(sprite);

		flagDiary = false;
	}

	
}
