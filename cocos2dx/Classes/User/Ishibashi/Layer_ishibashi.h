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
		void backButton();//ホームに戻るボタン

		void eatText();//食材説明用ウィンドウ
		void erase_eatText();

		void foodText(std::string commentary);//食材説明
		void erase_foodText();

		void eatTexture(int food_num);//食材描画用 仮引数で描画するものを変更
		void erase_eatTexture();//暫定使用中 重くなったら削除して考える

		void eatMenu();//食材選択用ウィンドウ
		void selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type);

		void eat_time(std::string eatTime);//時間表示？

		void character();//キャラクター描画

		void animation(int anime_num);//アニメーション

	public:
		bool exist;//食べ物画像用
		bool reside;//決定の有無用
		bool time = true;
		int animation_num = 0;
		cocos2d::Sprite * food;
		
		//食べ物名
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

		//食べ物画像
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

		//食べ物解説
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