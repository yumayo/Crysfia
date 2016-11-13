# ifndef __LayerDiary__
# define __LayerDiary__

# include "cocos2d.h"
#include "../LayerBase.h"
#include "ui/CocosGUI.h"

namespace User
{
    class LayerDiary : public LayerBase
    {
    public:
        LayerDiary( );
        ~LayerDiary( );

		bool init()override;
		void createGameStartButton();
		void touchEvent(Ref* pSneder, cocos2d::ui::TouchEventType type);
		void touch_feature();
		void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
		void selectDiary(int num);

		CREATE_FUNC(LayerDiary);
    private:

		enum MenuType {
			button_1,
			button_2,
			button_3,
			button_4,

			MAX
		};

		std::vector<cocos2d::ui::Button*> menuButtons;
    };
}

# endif // __LayerDiary__
