# ifndef __Layer_meal__
# define __Layer_meal__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
	class Layer_meal : public LayerBase
	{
	protected:
		void confirmButton();//����{�^����\������
		void backButton();//�z�[���ɖ߂�{�^��

		void eatText();//�H�ސ����p�E�B���h�E
		void erase_eatText();

		void foodText(std::string commentary);//�H�ސ���
		void erase_foodText();

		void eatTexture(int food_num);//�H�ޕ`��p �������ŕ`�悷����̂�ύX
		void erase_eatTexture();//�b��g�p�� �d���Ȃ�����폜���čl����

		void eatMenu();//�H�ޑI��p�E�B���h�E
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

		void eat_time(std::string eatTime);//���ԕ\���H

		void character();//�L�����N�^�[�`��

		void animation(int anime_num);//�A�j���[�V����

	public:
		bool exist;//�H�ו��摜�p
		bool reside;//����̗L���p
		bool time = true;
		int animation_num = 0;
		cocos2d::Sprite * food;
		
		//�H�ו���
		std::vector<std::string> food_name
		{
			"food_1",
			"food_2",
			"food_3",
			"food_4",
			"food_5",
			"food_6",
			"food_7",
			"food_8",
			"food_9",
			"food_10",
			"food_11",
			"food_12",
			"food_13",
			"food_14",
			"food_15",
		};

		//�H�ו��摜
		std::vector<std::string> food_texture
		{
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
			"schwb_mu.png",
			"chihyaa.png",
			"harukasan.png",
		};

		//�H�ו����
		std::vector<std::string> food_commentary
		{
			u8"schwb_mu.png",
			u8"chihyaa.png",
			u8"harukasan.png",
			u8"schwb_mu.png",
			u8"chihyaa.png",
			u8"harukasan.png",
			u8"schwb_mu.png",
			u8"chihyaa.png",
			u8"harukasan.png",
			u8"schwb_mu.png",
			u8"chihyaa.png",
			u8"harukasan.png",
			u8"schwb_mu.png",
			u8"chihyaa.png",
			u8"harukasan.png",
		};

		CREATE_FUNC(Layer_meal);
		Layer_meal();
		~Layer_meal();
		bool init() override;
		void setup() override;
		void update(float delta) override;
	};
}

# endif // __Layer_meal__