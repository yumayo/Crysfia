#include "Layer_ishibashi.h"

#define BUTTON_POS_X 340//ボタンの位置(x)
#define BUTTON_POS_Y 120//ボタンの位置(y)

USING_NS_CC;

namespace User
{
	Layer_meal::Layer_meal()
	{
	}
	Layer_meal::~Layer_meal()
	{
	}
	bool Layer_meal::init()
	{
		if (!Layer::init()) return false;

		food = Sprite::create();

		this->scheduleUpdate();

		exist = false;

		eatMenu();
		eatText();
		backButton();
		if (time) 
		{
			eat_time("lunch");//一回目
		}
		else
		{
			eat_time("dinner");//二回目
		}

		return true;
	}
	void Layer_meal::setup()
	{
		//メニュー表
	}
	void Layer_meal::update(float delta)
	{

	}

	//食事のメニュー用の説明文
	void Layer_meal::eatText()
	{

		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 600, 200));
		sprite->setColor(Color3B::WHITE);
		sprite->setName("Text");
		

		float x = 365;
		float y = 200;
		sprite->setPosition(Point(x, y));
		this->addChild(sprite);

		confirmButton();
	}

	//ウィンドウもどき削除用
	void Layer_meal::erase_eatText()
	{
		this->removeChildByName("Text");
	}

	//決定ボタン
	void Layer_meal::confirmButton()
	{
		//ボタンを作成する
		ui::Button * button = ui::Button::create("button.png");
		button->setTouchEnabled(true);
		//button->loadTextures(, "");

		//ボタンの位置設定
		button->setPosition(Vec2(600, 200));

		//ボタンに表示する文字
		// テキスト
		button->setTitleText(u8"決定");
		// フォント
		button->setTitleFontName("Arial");
		// フォントサイズ
		button->setTitleFontSize(20);
		// フォントカラー
		button->setTitleColor(Color3B::BLACK);
		button->setName("delite");

		//決定ボタン内容
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
		{
			erase_eatTexture();
			this->removeChildByName("delite");
			reside = false;
			character();
			animation(animation_num);
		});

		addChild(button);
	}

	//ホームボタン
	void Layer_meal::backButton()
	{
		//ボタンを作成する
		ui::Button * button = ui::Button::create("button.png");
		button->setTouchEnabled(true);

		//ボタンの位置設定
		button->setPosition(Vec2(125, 1100));

		//ボタンに表示する文字
		// テキスト
		button->setTitleText("Back");
		// フォント
		button->setTitleFontName("Arial");
		// フォントサイズ
		button->setTitleFontSize(20);
		// フォントカラー
		button->setTitleColor(Color3B::BLACK);

		//ホームボタン内容
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
		{

		});

		addChild(button);
	}

	void Layer_meal::eatMenu()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto listView = ui::ListView::create();
		listView->setContentSize(Size(400, 700));
		listView->setPosition(Vec2(550, 400));
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setBounceEnabled(true);
		this->addChild(listView);

		//15つのコンテンツの作成
		for (int i = 0; i < food_name.size(); ++i)
		{
			//レイアウトに表示するボタンを作成
			auto button = ui::Button::create("button.png", "");//ボタン画像
			button->setScale9Enabled(true);
			button->setPosition(button->getContentSize() / 2);
			button->setTitleText(food_name[i]);//食べ物　アイテム名

			//ボタンを押したときの反応
			button->addTouchEventListener([this, i](Ref* button, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					/*if (exist)
					{
						eatTexture(i);
					}
					else
					{
						food = Sprite::create("res/texture/" + food_texture[i]);
						food->setPosition(Vec2(285, 800));
						food->setName("eraseFood");
						this->addChild(food);



						exist = true;
					}*/
					if (reside) 
					{
						erase_eatTexture();
						eatTexture(i);

						animation_num = i;

						erase_foodText();
						foodText(food_commentary[i]);
					}
				}
			});
			//レイアウトを作成
			auto layout = ui::Layout::create();
			layout->setContentSize(button->getContentSize());
			layout->addChild(button);
			listView->addChild(layout);
		}
	}

	void Layer_meal::foodText(std::string commentary)
	{
		auto text = Label::createWithSystemFont(commentary, "Arial", 48);
		text->setPosition(Point(300, 200));
		text->setColor(ccc3(255, 0, 0));
		text->setName("commentary_text");
		this->addChild(text);
	}

	void Layer_meal::erase_foodText()
	{
		this->removeChildByName("commentary_text");
	}

	void Layer_meal::selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type)
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

	/*void Layer_meal::eatTexture(int food_num)
	{
		food->setSpriteFrame(Sprite::create("res/texture/" + food_texture[food_num])->getSpriteFrame());
	}*/

	void Layer_meal::eatTexture(int food_num)
	{
		food = Sprite::create("res/texture/" + food_texture[food_num]);
		food->setPosition(Vec2(285, 800));
		food->setName("eraseFood");
		this->addChild(food);
	}

	void Layer_meal::erase_eatTexture()
	{
		this->removeChildByName("eraseFood");
	}

	void Layer_meal::eat_time(std::string eatTime)
	{
		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 100, 50));
		sprite->setColor(Color3B::WHITE);
		sprite->setPosition(Point(250,1100));
		this->addChild(sprite);

		auto text = Label::createWithSystemFont(eatTime, "Arial", 24);
		text->setPosition(Point(250, 1100));
		text->setColor(ccc3(0, 0, 0));
		text->setName("time_text");
		this->addChild(text);
	}

	void Layer_meal::character()
	{
		cocos2d::Sprite * kuroe = Sprite::create(u8"res/texture/クロエ普通.png");
		kuroe->setScale(0.5);
		kuroe->setPosition(Vec2(285, 600));
		this->addChild(kuroe);
	}

	void Layer_meal::animation(int anime_num)
	{
		food = Sprite::create("res/texture/" + food_texture[anime_num]);
		food->setPosition(Vec2(280, 1050));
		food->setScale(0.1);
		this->addChild(food);

		CCFiniteTimeAction* move = CCMoveTo::create(1.0f, ccp(280, 850));
		food->runAction(move);

		//フェード 1秒で、100%へ  
		CCFiniteTimeAction* fade = CCFadeTo::create(1.0f, 0);
		food->runAction(fade);
	}
}