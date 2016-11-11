#include "UIManager.h"
#include "Test.h"
#include "BGManager.h"
#include "../SceneManager.h"
#include "cocos2d/external/json/rapidjson.h"
#include "cocos2d/external/json/document.h"

USING_NS_CC;

namespace User
{
	UIManager::UIManager() :
		winSize(Director::getInstance()->getVisibleSize()),
		origin(Director::getInstance()->getVisibleOrigin()),
		pos(Director::getInstance()->getVisibleSize() / Director::getInstance()->getContentScaleFactor()),
		menuWindow(nullptr),
		swicthWindow(nullptr),
		optionIcon(nullptr),
		isOpen(false),
		menuButtons(std::vector<ui::Button*>()),
		subButtons(std::vector<ui::Button*>()),
		sliderBers(std::vector<ui::Slider*>()),
		optionLabels(std::vector<Label*>())
	{
		bgManager = BGManager::create();
	}

	UIManager::~UIManager() {}

	bool UIManager::init()
	{
		if (!Layer::init()) { return false; }
		
		this->addChild(bgManager, (int)zOder::BACKGROUND, (int)LayerType::BACGROUND);
		createDiaryWindow();
		createSubMenuWindow();
		createMainMenuWindow();
		return true;
	}

	void UIManager::createMainMenuWindow()
	{
		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(pos.x * 0, pos.y * 0.f));
		layout->setContentSize(Size(winSize.x, 150));

		//メニューの背景
		auto menuImage = ui::Scale9Sprite::create("res/Image/WindowBase/WinBase_88.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				120 / CC_CONTENT_SCALE_FACTOR(), 120 / CC_CONTENT_SCALE_FACTOR()),
			Rect(32 / CC_CONTENT_SCALE_FACTOR(), 32 / CC_CONTENT_SCALE_FACTOR(),
				64 / CC_CONTENT_SCALE_FACTOR(), 64 / CC_CONTENT_SCALE_FACTOR()));
		menuImage->setPosition(layout->getContentSize().width / 2, layout->getContentSize().height * 0.5f);
		menuImage->setContentSize(layout->getContentSize());
		layout->addChild(menuImage);
		Vec2 menuLayout = layout->getContentSize();

		//jsonファイルの読み込み
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("res/json/mainMenuUI.json");
		rapidjson::Document doc;

		//jsonファイルをパース
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["Button"];
			for (rapidjson::SizeType i = 0; i < buttonsData.Size(); i++)
			{
				menuButtons.push_back(ui::Button::create(buttonsData[i]["res"].GetString()));
				menuButtons[i]->setTitleText(buttonsData[i]["name"].GetString());
				menuButtons[i]->setTitleFontSize(42);
				menuButtons[i]->setTitleColor(Color3B::WHITE);

				float x = buttonsData[i]["pos"]["x"].GetDouble();
				float y = buttonsData[i]["pos"]["y"].GetDouble();

				menuButtons[i]->setPosition(Vec2(menuLayout.x * x, menuLayout.y * y));
				layout->addChild(menuButtons[i], 1, i);

				menuButtons[i]->addTouchEventListener(CC_CALLBACK_2(UIManager::touchEventOfMainMenu, this));
			}
		}
		this->addChild(layout, (int)zOder::SUB_MENU, (int)LayerType::MAIN_MENU);
	}

	//育成メニューの処理
	void UIManager::createSubMenuWindow()
	{
		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(pos.x, pos.y * 0));
		layout->setContentSize(Size(winSize.x, 150));

		//メニューの背景
		auto menuImage = ui::Scale9Sprite::create("res/Image/WindowBase/WinBase_88.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				120 / CC_CONTENT_SCALE_FACTOR(), 120 / CC_CONTENT_SCALE_FACTOR()),
			Rect(32 / CC_CONTENT_SCALE_FACTOR(), 32 / CC_CONTENT_SCALE_FACTOR(),
				64 / CC_CONTENT_SCALE_FACTOR(), 64 / CC_CONTENT_SCALE_FACTOR()));
		menuImage->setPosition(layout->getContentSize().width / 2, layout->getContentSize().height * 0.5f);
		menuImage->setContentSize(layout->getContentSize());
		layout->addChild(menuImage);
		Vec2 menuLayout = layout->getContentSize();

		//jsonファイルの読み込み
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("res/json/subMenuUI.json");
		rapidjson::Document doc;

		//jsonファイルをパース
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["Button"];
			for (rapidjson::SizeType i = (int)SubButtonType::BACK; i < buttonsData.Size(); i++)
			{
				subButtons.push_back(ui::Button::create(buttonsData[i]["res"].GetString()));
				subButtons[i]->setTitleText(buttonsData[i]["name"].GetString());
				subButtons[i]->setTitleFontSize(42);
				subButtons[i]->setTitleColor(Color3B::WHITE);

				float x = buttonsData[i]["pos"]["x"].GetDouble();
				float y = buttonsData[i]["pos"]["y"].GetDouble();

				subButtons[i]->setPosition(Vec2(menuLayout.x * x, menuLayout.y * y));
				layout->addChild(subButtons[i], 1, i + (int)SubButtonType::BACK);

				subButtons[i]->addTouchEventListener(CC_CALLBACK_2(UIManager::touchEventOfSubMenu, this));
			}
		}

		this->addChild(layout, (int)zOder::SUB_MENU, (int)LayerType::SUB_MENU);
	}

	void UIManager::createDiaryWindow()
	{
		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(pos.x, pos.y * 0));
		layout->setContentSize(Size(winSize.x, 150));

		
		this->addChild(layout, (int)zOder::DIARY_MENU, (int)LayerType::DIARY_MENU);
	}

	//各メニューボタンの処理
	/**************************************************
	TODO:
	残りの各ボタン移行の処理を書く。終わったら下のリストを消す
	日記
	設定
	***************************************************/
	void UIManager::touchEventOfMainMenu(Ref * pSender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::ENDED:

			if (pSender == menuButtons[(int)ButtonType::STORY]) { SceneManager::createIslandMap(); }
			if (pSender == menuButtons[(int)ButtonType::BREEDING]) { changeToSubWindow(); }
			if (pSender == menuButtons[(int)ButtonType::OPTION]) { setOptionWindow(); }
			if (pSender == menuButtons[(int)ButtonType::DIARY]) { changeToDiaryWindow(); }

		default:
			break;
		}
	}

	void UIManager::touchEventOfSubMenu(Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::CANCELED: break;
		case ui::Widget::TouchEventType::ENDED:
			if (pSender == subButtons[(int)SubButtonType::BACK]) { changeToMainWindow(); }
			if (pSender == subButtons[(int)SubButtonType::MEAL]) { }
			if (pSender == subButtons[(int)SubButtonType::CLOTHES]) { }
			if (pSender == subButtons[(int)SubButtonType::CLEANING]) { }
		default:
			break;
		}
	}

	//育成メニューからメインメニューへ戻す関数です
	void UIManager::changeToMainWindow()
	{
		auto m = this->getChildByTag((int)LayerType::MAIN_MENU);
		auto s = this->getChildByTag((int)LayerType::SUB_MENU);
		
		//auto 
		
		swapWindow(s, m);
		bgManager->changeBackGround( (int)BGType::MAIN_MENU, (int)BGType::BREEDING_MENU);
	}

	//メインメニューからサブメニューへ変更する関数です
	void UIManager::changeToSubWindow()
	{
		auto m = this->getChildByTag((int)LayerType::MAIN_MENU);
		auto s = this->getChildByTag((int)LayerType::SUB_MENU);
		swapWindow(m, s);

		bgManager->changeBackGround((int)BGType::BREEDING_MENU, (int)BGType::MAIN_MENU);
	}

	void UIManager::changeToDiaryWindow()
	{
		auto m = this->getChildByTag((int)LayerType::MAIN_MENU);
		auto d = this->getChildByTag((int)LayerType::DIARY_MENU);
		swapWindow(m,d);
		bgManager->changeBackGround((int)BGType::DIARY_MENU, (int)BGType::MAIN_MENU);
	}

	//レイヤーを入れ替える関数です。現在はNodeの指定しかできないです
	//TODO:Pos指定、移動時間の指定、遅延時間の指定をできるようにする。
	void UIManager::swapWindow(Node * moveOutObj, Node * moveInObj)
	{
		auto size = Director::getInstance()->getVisibleSize();
		auto moveOut = MoveBy::create(0.3f, Vec2(size.width, 0));
		moveOutObj->runAction(moveOut);

		auto moveIn = MoveBy::create(0.3f, Vec2(-size.width, 0));
		auto delay = DelayTime::create(0.5f);
		moveInObj->runAction(Sequence::create(delay, moveIn, nullptr));
	}

	//オプションウィンドウの生成
	//TODO:Pos指定、Size指定、画像指定をできるようにする。
	void UIManager::setOptionWindow()
	{
		Size winSize = Size(Director::getInstance()->getVisibleSize().width + 80,
		Director::getInstance()->getVisibleSize().height);
		Size contentWinSize = Size(500, 600);

		auto list = ui::ListView::create();
		list->setContentSize(winSize);
		this->addChild(list, (int)zOder::OPTION, (int)LayerType::OPTION);

		auto layout = ui::Layout::create();
		layout->setContentSize(list->getContentSize());
		list->addChild(layout);
		auto layoutSize = layout->getContentSize();

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
			auto option = this->getChildByTag((int)LayerType::OPTION);
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				this->removeChild(option);
			}
		});
	}
}