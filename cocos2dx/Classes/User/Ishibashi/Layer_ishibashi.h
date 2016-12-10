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
		//void backButton();//�z�[���ɖ߂�{�^��

		void eatText();//�H�ސ����p�E�B���h�E

		void foodText(std::string commentary, int y);//�H�ސ���
		void eraseFoodText();

		//void eatButton(int food_num);//�H�ޕ`��p �������ŕ`�悷����̂�ύX

		void Menu();//�I��p�E�B���h�E
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

		void eatTime(std::string eatTime);//���ԕ\���H

		void character();//�L�����N�^�[�`��

		void animation(int anime_num);//�A�j���[�V����

		void normalButton(int text_number,std::string button_photo, int normalButtonTag);//�{�^���ėp�p

		void heart();//�D���x�\��(��)

		void buttonAudio(std::string audio_name, int volume);//���ʉ��ǂݍ��ݗp volume 0.0~1.0

		void mealDressVolume(int set);//���ʒ��ߗp

		void mealTutorial();//�`���[�g���A���p?

		void eraseMealTutorial();

		void loadData();

	public:
		bool exist;//�H�ו��摜�p
		bool reside;//����̗L���p
		int change;//�H���ƒ��ւ�
		int audio_volume = 1.0f;
		int animation_num = 0;//�A�j���[�V�����ԍ�
		cocos2d::Sprite * food;//�A�j���[�V�����p�摜

		enum situation
		{
			meal,
			dressClothes,
		};
		
		//�H�ו��摜
		std::vector<std::string> food_button;

		//�H�ו��擾�L��
		std::vector<bool> food_gain;
		
		//�ߑ��摜
		std::vector<std::string> dress_button;

		//�ߑ��̗L��
		std::vector<bool> dress_gain;

		//�ߑ����
		std::vector<std::string> dress_commentary
		{
			u8"���i��",
			u8"dress_B.png",
			u8"dress_C.png",
			u8"dress_D.png",
			u8"dress_E.png",
		};

		//�H�ו����
		std::vector<std::string> food_commentary
		{
			u8"�p����",
			u8"��",
			u8"�ʕ�",
			u8"������",
			u8"���",
		};

		CREATE_FUNC(Layer_meal);
		Layer_meal();
		~Layer_meal();

		bool init()override;
		void setup() override;
		void update(float delta) override;

		void setLayer(int _layerName);
	};
}

# endif // __Layer_meal__