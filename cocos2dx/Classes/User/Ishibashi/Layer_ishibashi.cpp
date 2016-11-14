#include "Layer_ishibashi.h"

#define BUTTON_POS_X 340//ボタンの位置(x)
#define BUTTON_POS_Y 120//ボタンの位置(y)

USING_NS_CC;

namespace User
{
	Layer_ishibashi::Layer_ishibashi()
	{
	}
	Layer_ishibashi::~Layer_ishibashi()
	{
	}
	bool Layer_ishibashi::init()
	{
		if (!Layer::init()) return false;

		food = Sprite::create();

		this->scheduleUpdate();

		exist = false;

		eatMenu();
		eatText();

		return true;
	}
	void Layer_ishibashi::setup()
	{
		//メニュー表
	}
	void Layer_ishibashi::update(float delta)
	{

	}

	//食事のメニュー用の説明文
	void Layer_ishibashi::eatText()
	{

		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 600, 200));
		sprite->setColor(Color3B::WHITE);
		sprite->setName("Text");

		float x = 365;
		float y = 200;
		sprite->setPosition(Point(x, y));
		this->addChild(sprite);

		showButton();
	}

	//ウィンドウもどき削除用
	void Layer_ishibashi::erase_eatText()
	{
		this->removeChildByName("Text");
	}

	void Layer_ishibashi::showButton()
	{
		//ボタンを作成する
		ui::Button * button = ui::Button::create();
		button->setTouchEnabled(true);
		button->loadTextures( "res/texture/button.png", "res/texture/button.png" );

		//ボタンの位置設定
		button->setPosition(Vec2(600, 200));

		//ボタンに表示する文字
		// テキスト
		button->setTitleText("Confirm");
		// フォント
		button->setTitleFontName("res/fonts/Arial");
		// フォントサイズ
		button->setTitleFontSize(20);
		// フォントカラー
		button->setTitleColor(Color3B::BLACK);

		//決定ボタン
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
		{

		});

		addChild(button);
	}

	void Layer_ishibashi::eatMenu()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto listView = ui::ListView::create();
		listView->setContentSize(Size(400, 700));//defult Size(240,320)
		listView->setPosition(Vec2(550, 400));
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setBounceEnabled(true);
		this->addChild(listView);

		//eatTexture();

		//15つのコンテンツの作成
		for (int i = 0; i < food_name.size(); ++i)
		{
			//レイアウトに表示するボタンを作成
			auto button = ui::Button::create("res/texture/button.png", "res/texture/button.png" );//ボタン画像
			button->setScale9Enabled(true);
			button->setPosition(button->getContentSize() / 2);
			button->setTitleText(food_name[i]);//食べ物　アイテム名

			//ボタンを押したときの反応
			button->addTouchEventListener([this, i](Ref* button, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					if (exist)
					{
						eatTexture(i);
					}
					else
					{
						food = Sprite::create("res/texture/" + food_texture[i]);
						food->setPosition(Vec2(200, 400));
						this->addChild(food);
						exist = true;
					}
				}
			});
			//CCLOG("%d\n", food_name[i]);
			//レイアウトを作成
			auto layout = ui::Layout::create();
			layout->setContentSize(button->getContentSize());
			layout->addChild(button);
			listView->addChild(layout);
		}
	}

	void Layer_ishibashi::selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type)
	{
		switch (type)
		{
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Item Start Index = %ld", listView->getCurSelectedIndex());
			break;
		}//
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Child End Index = %ld", listView->getCurSelectedIndex());
			break;
		}
		default:
			break;
		}
	}

	void Layer_ishibashi::eatTexture(int food_num)
	{
		food->setSpriteFrame(Sprite::create("res/texture/" + food_texture[food_num])->getSpriteFrame());
	}

	//void Layer_ishibashi::erase_eatTexture(int erase_num)
	//{

	//}
}