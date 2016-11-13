#include "LayerDiary.h"

#include "../SceneManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;

namespace User
{
    LayerDiary::LayerDiary( )
    {
        
    }
    LayerDiary::~LayerDiary( )
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

		// ゲームスタートボタン
		createGameStartButton();


		// リストビューの作成
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleSize();
		
		auto listView = cocos2d::ui::ListView::create();
		listView->setContentSize(Size(250, 500));
		listView->setPosition((visibleSize - listView->getContentSize()) / 2);
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setBounceEnabled(true);
		this->addChild(listView);
		
		// 30つのコンテンツを作成
		for (int i = 0; i <= 30; i++) {
			// レイアウトに表示するボタンを作成
			
			menuButtons.push_back(ui::Button::create("res/image/WindowBase/WinBase_8.png", "res/image/WindowBase/WinBase_9.png"));
			menuButtons[i]->setScale9Enabled(true);
			menuButtons[i]->setContentSize(Size(240, 60));
			menuButtons[i]->setPosition(menuButtons[i]->getContentSize() / 2);
			menuButtons[i]->setTitleFontSize(20);
			menuButtons[i]->setTitleText(StringUtils::format("Button No: %d", i));

			menuButtons[i]->addTouchEventListener([=](Ref* pSender, ui::Button::TouchEventType type) {
			
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					if (pSender == menuButtons[i]) {
						selectDiary(i + 1);
					}
					break;
				case cocos2d::ui::Widget::TouchEventType::MOVED:
					break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					break;
				case cocos2d::ui::Widget::TouchEventType::CANCELED:
					break;
				default:
					break;
				}
			});

			//menuButtons[i]->setScale(0.5);
			// x,y座標をi * とかして調整する
			//menuButtons[i]->setPosition(Vec2(250, 800 - (150 * i)));
			//this->addChild(menuButtons[i]);

			// レイアウトを作成
			auto layout = ui::Layout::create();
			layout->setContentSize(menuButtons[i]->getContentSize());
			layout->addChild(menuButtons[i],1,i);
			listView->addChild(layout);


			//menuButtons[i]->addTouchEventListener(CC_CALLBACK_2(touchEvent, this));
			Sprite* bgsprite = Sprite::create("res/Image/bg.jpg");
			bgsprite->setContentSize(winSize);
			bgsprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			this->addChild(bgsprite);
		}

		//listView->addEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));

        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );
            auto origin = Director::getInstance( )->getVisibleOrigin( );

            auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );
            this->addChild( button );

            auto tar = Size( 128, 128 );
            auto con = button->getContentSize( );
            auto sca = tar.height / con.height;
            button->setScale( sca, sca );
            button->setPosition( origin + tar / 2.0 );
            button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::ENDED )
                {
                    SceneManager::createBreeding( );
                }
            } );

        }

		return true;
	}

	void LayerDiary::createGameStartButton() {
		// 画面サイズを取得
		//auto winSize = Director::getInstance()->getVisibleSize();

		//for (int i = 0; i < MenuType::MAX; i++) {
		//	menuButtons.push_back(ui::Button::create("res/miku_off.png"));
		//	menuButtons[i]->setScale(0.5);
		//	// x,y座標をi * とかして調整する
		//	menuButtons[i]->setPosition(Vec2(250, 800 - (150 * i)));
		//	this->addChild(menuButtons[i]);

		//}

	}

	void LayerDiary::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type) {
		switch (type)
		{
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Item Start Index = %d", listView->getCurSelectedIndex());
			break;
		}
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Child End Index = %d", listView->getCurSelectedIndex());
			break;
		}
		default:
			break;
		}

	}

	void LayerDiary::touch_feature() {

	}

	void LayerDiary::touchEvent(Ref * pSneder, cocos2d::ui::TouchEventType type) {
		//menuButtons[0]->setTitleText("Touch");

			
	}

	void LayerDiary::selectDiary(int num) {
		auto sprite = Sprite::create(StringUtils::format("res/Image/WindowBase/WinBase_%d.png", num));
		this->addChild(sprite);
	}



}