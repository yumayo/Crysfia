# ifndef __UIManager__
# define __UIManager__

# include "cocos2d.h"
#include "../LayerBase.h"
#include "ui/CocosGUI.h"

namespace User
{
    class UIManager : public LayerBase
    {
	private:

		//描画順用ステータス
		enum zOder
		{
			Menu = 1,
			Option,

		};
		
		//メニューステータス
		enum MenuType
		{
			STORY,
			FOOD,
			CLOTHES,
			CLEANING,
			DIARY,
			
			MAX
		};

		bool isOpen;
		void update(float dt);

	public:

		CREATE_FUNC(UIManager);
		UIManager( );
        ~UIManager( );
		bool init();

		cocos2d::ui::ListView* menuWindow;
		cocos2d::ui::ListView* optionWindow;
		cocos2d::ui::Button* swicthWindow;
		cocos2d::ui::Button* optionIcon;
		std::vector<cocos2d::ui::Button*> menuButtons;
		
		void createOptionIcon();
		void createMenuWindow();
		void setOptionWindow();
    };
}

# endif // __UIControl__
