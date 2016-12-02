#include "Layer_ishibashi.h"

#define BUTTON_POS_X 340//�{�^���̈ʒu(x)
#define BUTTON_POS_Y 120//�{�^���̈ʒu(y)

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
			eat_time("lunch");//����
		}
		else
		{
			eat_time("dinner");//����
		}

		return true;
	}
	void Layer_meal::setup()
	{
		//���j���[�\
	}
	void Layer_meal::update(float delta)
	{

	}

	//�H���̃��j���[�p�̐�����
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

	//�E�B���h�E���ǂ��폜�p
	void Layer_meal::erase_eatText()
	{
		this->removeChildByName("Text");
	}

	//����{�^��
	void Layer_meal::confirmButton()
	{
		//�{�^�����쐬����
		ui::Button * button = ui::Button::create("button.png");
		button->setTouchEnabled(true);
		//button->loadTextures(, "");

		//�{�^���̈ʒu�ݒ�
		button->setPosition(Vec2(600, 200));

		//�{�^���ɕ\�����镶��
		// �e�L�X�g
		button->setTitleText(u8"����");
		// �t�H���g
		button->setTitleFontName("Arial");
		// �t�H���g�T�C�Y
		button->setTitleFontSize(20);
		// �t�H���g�J���[
		button->setTitleColor(Color3B::BLACK);
		button->setName("delite");

		//����{�^�����e
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

	//�z�[���{�^��
	void Layer_meal::backButton()
	{
		//�{�^�����쐬����
		ui::Button * button = ui::Button::create("button.png");
		button->setTouchEnabled(true);

		//�{�^���̈ʒu�ݒ�
		button->setPosition(Vec2(125, 1100));

		//�{�^���ɕ\�����镶��
		// �e�L�X�g
		button->setTitleText("Back");
		// �t�H���g
		button->setTitleFontName("Arial");
		// �t�H���g�T�C�Y
		button->setTitleFontSize(20);
		// �t�H���g�J���[
		button->setTitleColor(Color3B::BLACK);

		//�z�[���{�^�����e
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

		//15�̃R���e���c�̍쐬
		for (int i = 0; i < food_name.size(); ++i)
		{
			//���C�A�E�g�ɕ\������{�^�����쐬
			auto button = ui::Button::create("button.png", "");//�{�^���摜
			button->setScale9Enabled(true);
			button->setPosition(button->getContentSize() / 2);
			button->setTitleText(food_name[i]);//�H�ו��@�A�C�e����

			//�{�^�����������Ƃ��̔���
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
			//���C�A�E�g���쐬
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
		cocos2d::Sprite * kuroe = Sprite::create(u8"res/texture/�N���G����.png");
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

		//�t�F�[�h 1�b�ŁA100%��  
		CCFiniteTimeAction* fade = CCFadeTo::create(1.0f, 0);
		food->runAction(fade);
	}
}