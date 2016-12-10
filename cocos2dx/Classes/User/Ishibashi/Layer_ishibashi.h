# ifndef __Layer_meal__
# define __Layer_meal__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
	class Layer_meal : public LayerBase
	{
	protected:
		void confirmButton();//決定ボタンを表示する
		//void backButton();//ホームに戻るボタン

		void eatText();//食材説明用ウィンドウ

		void foodText(std::string commentary, int y);//食材説明
		void eraseFoodText();

		//void eatButton(int food_num);//食材描画用 仮引数で描画するものを変更

		void Menu();//選択用ウィンドウ
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

		void eatTime(std::string eatTime);//時間表示？

		void character();//キャラクター描画

		void animation(int anime_num);//アニメーション

		void normalButton(int text_number,std::string button_photo, int normalButtonTag);//ボタン汎用用

		void heart();//好感度表示(仮)

		void buttonAudio(std::string audio_name, int volume);//効果音読み込み用 volume 0.0~1.0

		void mealDressVolume(int set);//音量調節用

		void mealTutorial();//チュートリアル用?

		void eraseMealTutorial();

		void loadData();

	public:
		bool exist;//食べ物画像用
		bool reside;//決定の有無用
		int change;//食事と着替え
		int audio_volume = 1.0f;
		int animation_num = 0;//アニメーション番号
		cocos2d::Sprite * food;//アニメーション用画像

		enum situation
		{
			meal,
			dressClothes,
		};
		
		//食べ物画像
		std::vector<std::string> food_button;

		//食べ物取得有無
		std::vector<bool> food_gain;
		
		//衣装画像
		std::vector<std::string> dress_button;

		//衣装の有無
		std::vector<bool> dress_gain;

		//衣装解説
		std::vector<std::string> dress_commentary
		{
			u8"普段着",
			u8"dress_B.png",
			u8"dress_C.png",
			u8"dress_D.png",
			u8"dress_E.png",
		};

		//食べ物解説
		std::vector<std::string> food_commentary
		{
			u8"角砂糖",
			u8"花",
			u8"果物",
			u8"金平糖",
			u8"宝石",
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