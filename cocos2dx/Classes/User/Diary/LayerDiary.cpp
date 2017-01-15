#include <fstream>
#include "LayerDiary.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"

USING_NS_CC;
using namespace ui;
using namespace std;

namespace User
{
	LayerDiary::LayerDiary()
	{
#if _DEBUG
		diaryNum = 7;
#else
		diaryNum = UserDefault::getInstance()->getIntegerForKey(u8"日") <= 7 ?
			UserDefault::getInstance()->getIntegerForKey(u8"日") - 1 : 7;
#endif
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
		setBackButton(u8"res/texture/diary/exit.png", Vec2(winSize.width * 0.1f, winSize.height * 0.05f));
		setButtons(diaryNum);

		return true;
	}

	// ボタンをタッチしたときの反応
	void LayerDiary::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto diaryTexture = Button::create("res/texture/diary/background.png", "res/texture/diary/background.png");
			diaryTexture->setScale(0.5f);
			diaryTexture->setPosition(winSize / 2);
			diaryTexture->setName("diaryTexture");
			this->addChild(diaryTexture, 2);

			auto button = ui::Button::create(u8"res/texture/diary/exit.png");
			diaryTexture->addChild(button);
			button->setScale(2);
			button->setPosition(Vec2(winSize.width * 0.3f, winSize.height * 0.2f));
			button->addTouchEventListener([this,&diaryTexture](Ref* pSender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					AudioManager::getInstance()->playSe("res/sound/SE/click.mp3");
					this->removeChildByName("diaryTexture");
				}
			});

			auto scrollView = ui::ScrollView::create();
			scrollView->setInnerContainerSize(Size(1500, 5500));
			scrollView->setContentSize(Size(1500,2000));
			scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
			scrollView->setBounceEnabled(true);
			scrollView->setPosition(Vec2(winSize.width * 0.0f, winSize.height * 0.3f ));
			diaryTexture->addChild(scrollView);

			for (int i = 0; i < diaryNum; i++)
			{
				auto c = this->getChildByTag(i);
				if (pSender == c) {
					selectDiary(c->getName(), scrollView);
					log("%s", c->getName().c_str());
				}
			}

		}
	}

	//日記のシーンの背景を設定します
	//引数には背景画像の相対パスをいれてください
	void LayerDiary::setBackground(std::string _filePath)
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		auto background = Sprite::create(_filePath);
		background->setPosition(winSize / 2);
		background->setScale(1080.0f / 2150.0f);
		this->addChild(background, 0);
	}

	//日記のボタンを生成します
	//引数に生成したい個数を設定してください
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
			button->setName(StringUtils::format("diary_%d", i + 1));
			this->addChild(button, 1, i);

			button->addTouchEventListener(CC_CALLBACK_2(LayerDiary::touchEvent, this));
		}
	}

	void LayerDiary::setBackButton(std::string _filePath, Vec2 _pos)
	{
		// 戻るボタンの生成
		auto button = ui::Button::create(_filePath);
		addChild(button);
		button->setAnchorPoint(Vec2(0, 0));
		button->setPosition(_pos);
		button->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				AudioManager::getInstance()->playSe("res/sound/SE/click.mp3");
				SceneManager::createBreeding();
			}
		});
	}

	// ボタンをタッチされたらこれで画像を描画
	void LayerDiary::selectDiary(std::string _name, Node* _tagetNode)
	{
		//テキストファイルから日記の文字列を取得
		auto filePath = FileUtils::getInstance()->fullPathForFilename(StringUtils::format(u8"res/texture/diary/%s.txt", _name.c_str()));
		std::ifstream inFile(filePath);
		int i = 1;

		//std::ifstreamを使って一列ずつ描画
		for (std::string line; std::getline(inFile, line);) 
		{
			i++;
			auto label = Label::createWithSystemFont(line, "arial.ttf", 64);
			label->setPosition(Vec2(Director::getInstance()->getWinSize().width , Director::getInstance()->getWinSize().height * 4.3f - (128 * i)));
			label->setColor(Color3B::BLACK);
			_tagetNode->addChild(label);
			log("%s", line.c_str());
		}
	}
}
