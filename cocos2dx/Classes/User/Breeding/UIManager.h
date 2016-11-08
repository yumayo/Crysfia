# ifndef __UIManager__
# define __UIManager__

# include "cocos2d.h"
#include "../LayerBase.h"
#include "ui/CocosGUI.h"
#include "VariousStatus.h"

namespace User
{
	class UIManager : public LayerBase
	{
	private:

		bool isOpen;
		void update(float dt);
		bool init();

	public:

		CREATE_FUNC(UIManager);
		UIManager();
		~UIManager();

	private:

		std::string buttonTexts[MenuType::MAX] = {
			"STO\n RY",
			"BREE\nDING",
			"DIA\n RY",
			"OPT\nION"
		};

		cocos2d::ui::ListView*	menuWindow;
		cocos2d::ui::ListView*	optionWindow;
		cocos2d::ui::Button*	swicthWindow;
		cocos2d::ui::Button*	optionIcon;

		std::vector<cocos2d::ui::Button*> menuButtons;
		std::vector<cocos2d::ui::Slider*> sliderBers;
		std::vector<cocos2d::Label*>	  optionLabels;
		
		void touchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void createMenuWindow();
		void setOptionWindow();
		void setDiaryWindow();
	};
}

# endif // __UIControl__
