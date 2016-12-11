# ifndef __Layer_ishibashi__
# define __Layer_ishibashi__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
	class Layer_ishibashi : public LayerBase
	{
	protected:
<<<<<<< HEAD
		void showButton();//ƒ{ƒ^ƒ“‚ğ•\¦‚·‚é

		void eatText();//HŞà–¾
		void erase_eatText();

		void eatTexture(int food_num);//HŞ•`‰æ—p ‰¼ˆø”‚Å•`‰æ‚·‚é‚à‚Ì‚ğ•ÏX
		//void erase_eatTexture(int erase_num);
=======
		void confirmButton();//Œˆ’èƒ{ƒ^ƒ“‚ğ•\¦‚·‚é
		//void backButton();//ƒz[ƒ€‚É–ß‚éƒ{ƒ^ƒ“

		void eatText();//HŞà–¾—pƒEƒBƒ“ƒhƒE

		void foodText(std::string commentary, int y);//HŞà–¾
		void eraseFoodText();

		//void eatButton(int food_num);//HŞ•`‰æ—p ‰¼ˆø”‚Å•`‰æ‚·‚é‚à‚Ì‚ğ•ÏX
>>>>>>> 8651947... ç”»åƒå·®ã—æ›¿ãˆä»–

		void Menu();//‘I‘ğ—pƒEƒBƒ“ƒhƒE
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

<<<<<<< HEAD
	public:
		bool exist;
		cocos2d::Sprite * food;
		
		std::vector<std::string> food_name
=======
		void eatTime(std::string eatTime);//ŠÔ•\¦H

		void character();//ƒLƒƒƒ‰ƒNƒ^[•`‰æ

		void animation(int anime_num);//ƒAƒjƒ[ƒVƒ‡ƒ“

		void normalButton(int text_number,std::string button_photo, int normalButtonTag);//ƒ{ƒ^ƒ“”Ä—p—p

		void heart();//DŠ´“x•\¦(‰¼)

		void buttonAudio(std::string audio_name, int volume);//Œø‰Ê‰¹“Ç‚İ‚İ—p volume 0.0~1.0

		void mealDressVolume(int set);//‰¹—Ê’²ß—p

		void mealTutorial();//ƒ`ƒ…[ƒgƒŠƒAƒ‹—p?

		void eraseMealTutorial();

		void loadData();

	public:
		bool exist;//H‚×•¨‰æ‘œ—p
		bool reside;//Œˆ’è‚Ì—L–³—p
		int change;//H–‚Æ’…‘Ö‚¦
		int audio_volume = 1.0f;
		int animation_num = 0;//ƒAƒjƒ[ƒVƒ‡ƒ“”Ô†
		cocos2d::Sprite * food;//ƒAƒjƒ[ƒVƒ‡ƒ“—p‰æ‘œ

		enum situation
>>>>>>> 8651947... ç”»åƒå·®ã—æ›¿ãˆä»–
		{
			meal,
			dressClothes,
		};
<<<<<<< HEAD

		std::vector<std::string> food_texture
=======
		
		//H‚×•¨‰æ‘œ
		std::vector<std::string> food_button;

		//H‚×•¨æ“¾—L–³
		std::vector<bool> food_gain;
		
		//ˆß‘•‰æ‘œ
		std::vector<std::string> dress_button;

		//ˆß‘•‚Ì—L–³
		std::vector<bool> dress_gain;

		//ˆß‘•‰ğà
		std::vector<std::string> dress_commentary
>>>>>>> 8651947... ç”»åƒå·®ã—æ›¿ãˆä»–
		{
			u8"•’i’…",
			u8"dress_B.png",
			u8"dress_C.png",
			u8"dress_D.png",
			u8"dress_E.png",
		};

<<<<<<< HEAD
		CREATE_FUNC(Layer_ishibashi);
		Layer_ishibashi();
		~Layer_ishibashi();
		bool init() override;
=======
		//H‚×•¨‰ğà
		std::vector<std::string> food_commentary
		{
			u8"Šp»“œ",
			u8"‰Ô",
			u8"‰Ê•¨",
			u8"‹à•½“œ",
			u8"•óÎ",
		};

		CREATE_FUNC(Layer_meal);
		Layer_meal();
		~Layer_meal();

		bool init()override;
>>>>>>> 8651947... ç”»åƒå·®ã—æ›¿ãˆä»–
		void setup() override;
		void update(float delta) override;

		void setLayer(int _layerName);
	};
}

# endif // __Layer_ishibashi__