#include "UIManager.h"
#include "Test.h"
#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
	UIManager::UIManager() :
		menuWindow(nullptr),
		swicthWindow(nullptr),
		optionIcon(nullptr),
		isOpen(false)
	{
	}

	UIManager::~UIManager() {}

	bool UIManager::init()
	{
		if (!Layer::init()) { return false; }

		createMenuWindow();

		//this->scheduleUpdate();	update()関数を使うときはコメントアウトを外す
		return true;
	}

	void UIManager::createMenuWindow()
	{
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Vec2 winSize = Director::getInstance()->getWinSize();

		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(620, 10));
		layout->setContentSize(Size(winSize.x, 150));
		auto layoutSize = layout->getContentSize();

#if _DEBUG //デバッグ時、layoutを黒くする
		auto bg = LayerColor::create(Color4B::BLACK, layoutSize.width, layoutSize.height);
		bg->setOpacity(128);
		layout->addChild(bg);
#endif //_DEBUG

		//メニューの背景
		auto menuImage = ui::Scale9Sprite::create("res/Image/WindowBase/WinBase_88.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				120 / CC_CONTENT_SCALE_FACTOR(), 120 / CC_CONTENT_SCALE_FACTOR()),
			Rect(32 / CC_CONTENT_SCALE_FACTOR(), 32 / CC_CONTENT_SCALE_FACTOR(),
				64 / CC_CONTENT_SCALE_FACTOR(), 64 / CC_CONTENT_SCALE_FACTOR()));
		menuImage->setPosition(layoutSize / 2);
		menuImage->setContentSize(layout->getContentSize());
		layout->addChild(menuImage);

		//メニューウィンドウの開閉用ボタン
		swicthWindow = ui::Button::create("res/Image/WindowBase/WinBase_1.png");
		swicthWindow->setScaleX(0.25f);
		swicthWindow->setScaleY(0.5f);
		swicthWindow->setPosition(Vec2(60, layoutSize.height / 2));
		layout->addChild(swicthWindow);

		for (int i = 0; i < MenuType::MAX; i++)
		{
			menuButtons.push_back(ui::Button::create("res/Image/WindowBase/WinBase_24.png"));
			menuButtons[i]->setScale(0.7);
			menuButtons[i]->setTitleText(buttonTexts[i]);
			menuButtons[i]->setTitleFontSize(42);
			menuButtons[i]->setTitleColor(Color3B::WHITE);
			menuButtons[i]->setPosition(Vec2(130 * (i + 1.5f), layoutSize.height / 2));
			layout->addChild(menuButtons[i]);

			menuButtons[i]->addTouchEventListener(CC_CALLBACK_2(UIManager::touchEvent, this));
		}

		this->addChild(layout, 0, zOder::Menu);

		/**************************************
					各ボタンUIの処理
		***************************************/

		//メニュー開閉用ボタン
		swicthWindow->addTouchEventListener([&](Ref *pSender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				auto m = getChildByTag(zOder::Menu);
				isOpen = !isOpen;
				if (!isOpen) {
					auto action = MoveBy::create(0.2f, Vec2(620, 0));
					m->runAction(action);
				}
				else if (isOpen) {
					auto action = MoveBy::create(0.2f, Vec2(-620, 0));
					m->runAction(action);
				}
			}
		});
	}

	//各メニューボタンの処理
	/**************************************************
	TODO:
	残りの各ボタンの処理を書く。終わったら下のリストを消す
	ストーリー、
	お世話、
	日記
	設定
	***************************************************/
	void UIManager::touchEvent(Ref * pSender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::ENDED:

			if (pSender == menuButtons[MenuType::STORY])	{ SceneManager::createIslandMap(); }
			if (pSender == menuButtons[MenuType::BREEDING]) {}
			if (pSender == menuButtons[MenuType::OPTION])	{ setOptionWindow(); }
			if (pSender == menuButtons[MenuType::DIARY])	{ setDiaryWindow();	}

		default:
			break;
		}
	}

	//オプションウィンドウの生成
	void UIManager::setOptionWindow()
	{
		Size winSize = Size(Director::getInstance()->getVisibleSize().width + 80,
			Director::getInstance()->getVisibleSize().height);
		Size contentWinSize = Size(500, 600);

		auto list = ui::ListView::create();
		list->setContentSize(winSize);
		this->addChild(list, 0, Option);

		auto layout = ui::Layout::create();
		layout->setContentSize(winSize);
		list->addChild(layout);

		auto layoutSize = layout->getContentSize();

#if _DEBUG
		auto bg = LayerColor::create(Color4B::WHITE, layout->getContentSize().width, layout->getContentSize().height);
		bg->setOpacity(128);
		layout->addChild(bg);
#endif //_DEBUG

		auto menuImage = ui::Scale9Sprite::create("res/Image/WindowBase/WinBase_59.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				120 / CC_CONTENT_SCALE_FACTOR(), 120 / CC_CONTENT_SCALE_FACTOR()),
			Rect(32 / CC_CONTENT_SCALE_FACTOR(), 32 / CC_CONTENT_SCALE_FACTOR(),
				64 / CC_CONTENT_SCALE_FACTOR(), 64 / CC_CONTENT_SCALE_FACTOR()));

		//オプションウィンドウの位置。修正した値
		auto winPos = Vec2(list->getContentSize().width / 2 - 40, list->getContentSize().height / 2);
		menuImage->setPosition(winPos);
		menuImage->setContentSize(contentWinSize);
		layout->addChild(menuImage);

		//CloseButton（仮置き）
		auto closeButton = ui::Button::create("res/Image/WindowBase/WinBase_18.png");
		closeButton->setTitleFontSize(48);
		closeButton->setTitleText("CLO\n SE");
		closeButton->setScaleX(0.7f);
		closeButton->setScaleY(0.6f);
		closeButton->setPosition(Vec2(winPos.x, winPos.y - 200));
		layout->addChild(closeButton);

		//CloseButtonの処理
		//ボタンを押したときにLayerに追加されているOptionタグを持つ子ノードを取得しLayerから外している
		closeButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
			auto option = this->getChildByTag(Option);
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				this->removeChild(option);
			}
		});
	}

	void UIManager::setDiaryWindow()
	{
		Size winSize = Director::getInstance()->getVisibleSize();
		Size contentWinSize = Size(300, 600);

		auto list = ui::ListView::create();
		list->setContentSize(winSize);
		this->addChild(list, 0, DIARY);

		auto layout = ui::Layout::create();
		layout->setContentSize(winSize);
		list->addChild(layout);

		auto layoutSize = layout->getContentSize();

		auto menuImage = ui::Scale9Sprite::create("res/Image/WindowBase/WinBase_58.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				120 / CC_CONTENT_SCALE_FACTOR(), 120 / CC_CONTENT_SCALE_FACTOR()),
			Rect(32 / CC_CONTENT_SCALE_FACTOR(), 32 / CC_CONTENT_SCALE_FACTOR(),
				64 / CC_CONTENT_SCALE_FACTOR(), 64 / CC_CONTENT_SCALE_FACTOR()));

		//オプションウィンドウの位置。修正した値
		auto winPos = Vec2(list->getContentSize().width / 2 - 40, list->getContentSize().height / 2);
		menuImage->setPosition(winPos);
		menuImage->setContentSize(contentWinSize);
		layout->addChild(menuImage);

		//CloseButton（仮置き）
		auto closeButton = ui::Button::create("res/Image/WindowBase/WinBase_18.png");
		closeButton->setTitleFontSize(48);
		closeButton->setTitleText("CLO\n SE");
		closeButton->setScaleX(0.7f);
		closeButton->setScaleY(0.6f);
		closeButton->setPosition(Vec2(winPos.x, winPos.y - 200));
		layout->addChild(closeButton);

		//CloseButtonの処理
		//ボタンを押したときにLayerに追加されているOptionタグを持つ子ノードを取得しLayerから外している
		closeButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
			auto option = this->getChildByTag(Option);
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				this->removeChild(option);
			}
		});
	}



	//TIPS: UIのListViewやLayoutの原点位置はSpriteなど中央ではなく左下になっている    

	void UIManager::update(float dt)
	{
	}

}
