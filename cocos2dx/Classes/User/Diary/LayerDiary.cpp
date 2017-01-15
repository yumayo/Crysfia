#include <fstream>
#include "LayerDiary.h"
#include "../SceneManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;

namespace User
{
	LayerDiary::LayerDiary()
	{
		//diaryNum = UserDefault::getInstance()->getIntegerForKey(u8"日") - 1;
		diaryNum = 9;
	}
	LayerDiary::~LayerDiary()
	{

	}

	bool LayerDiary::init() {

		if (!Layer::init()) { return false; }

		// 画面サイズを取得
		Size winSize = Director::getInstance()->getVisibleSize();
		//背景の設定
		setBackground("res/texture/diary/background.png");
		setButtons(diaryNum);

		//// リストビューの作成
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//Vec2 origin = Director::getInstance()->getVisibleSize();

		//listView = cocos2d::ui::ListView::create();
		//listView->setContentSize(Size(700, 800));
		//listView->setPosition((visibleSize - listView->getContentSize()) / 2);
		//listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		//listView->setBounceEnabled(true);
		//listView->setTag(0);
		//this->addChild(listView);



		//// ボタンの生成
		//for (int i = 0; i < 6; ++i)
		//{
		//	auto node = ui::Layout::create();
		//	node->setTag(i);
		//	for (int k = 0; k < 3; k++)
		//	{
		//		auto button = ui::Button::create("res/Image/WindowBase/WinBase_8.png", "res/Image/WindowBase/WinBase_9.png");
		//		node->addChild(button);
		//		button->setTag(i);
		//		button->setName(StringUtils::format("miku_%d", k));
		//		button->setPosition(Vec2(150 + k * 200, 100));
		//		button->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

		//		node->setContentSize(Size(visibleSize.width, button->getContentSize().height + 100));
		//	}
		//	listView->addChild(node);
		//}

		//// 日記を開いているかどうか
		//flagDiary = false;


		// 戻るボタンの生成
		{
			auto scale = Director::getInstance()->getContentScaleFactor();

			auto button = ui::Button::create(u8"res/texture/diary/exit.png");
			addChild(button);
			button->setAnchorPoint(Vec2(0, 0));
			button->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.05f));
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

			for (int i = 0; i < diaryNum; i++)
			{
				auto c = this->getChildByTag(i);
				if (pSender == c) {
					selectDiary(c->getName());
					log("%s", c->getName().c_str());
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

	void LayerDiary::setBackground(std::string _filePath)
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		auto background = Sprite::create(_filePath);
		background->setPosition(winSize / 2);
		background->setScale(1080.0f / 2150.0f);
		this->addChild(background, 0);
	}

	void LayerDiary::setButtons(int _buttonCount)
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		Vec2 pos = Vec2(0, 1200);

		for (int i = 0; i < _buttonCount; i++)
		{
			pos.x += winSize.width / 4;

			if (i % 3 == 0) {
				pos.x = winSize.width / 4;
				pos.y -= 160;
			}

			auto button = Button::create(StringUtils::format("res/texture/diary/diary_%d.png", (i + 1)));
			button->setPosition(Vec2(pos.x, pos.y));
			button->setScale(0.8f);
			button->setName(StringUtils::format("diary_%d", i + 1 ) );
			this->addChild(button, 1, i);

			button->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));
		}
	}

	// ボタンをタッチされたらこれで画像を描画
	void LayerDiary::selectDiary(std::string _name)
	{
		auto filePath = FileUtils::getInstance()->fullPathForFilename( StringUtils::format("res/texture/diary/%s.txt", _name.c_str() ) );
		std::ifstream inFile(filePath);
		int i = 1;
		for (std::string line; std::getline(inFile, line);) {
			// ここに処理を記述
			i++;
			auto label = Label::createWithSystemFont(line, "arial.ttf", 32);
			label->setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height / 2 - (32*i) ) );
			label->setColor(Color3B::BLACK);
			this->addChild(label);
			log("%s", line.c_str());
		}

		//auto label = Label::createWithSystemFont();
		/*auto sprite = Sprite::create(StringUtils::format("res/texture/diary/%s.txt", _name.c_str()));
		sprite->setPosition(Vec2(200, 500));
		this->addChild(sprite);
		*/flagDiary = false;
	}
}
