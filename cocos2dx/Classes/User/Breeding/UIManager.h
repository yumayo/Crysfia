# ifndef __UIManager__
# define __UIManager__

# include "cocos2d.h"
#include "../LayerBase.h"
#include "BGManager.h"
#include "ui/CocosGUI.h"
#include "User/Breeding/VariousStatus.h"

namespace User
{
	class UIManager : public LayerBase
	{
	private:

		bool isOpen;
		//void update(float dt);
		bool init();

	public:

		CREATE_FUNC(UIManager);
		UIManager();
		~UIManager();

	private:
		BGManager* bgManager;
		cocos2d::ui::ListView*	menuWindow;
		cocos2d::ui::ListView*	optionWindow;
		cocos2d::ui::Button*	swicthWindow;
		cocos2d::ui::Button*	optionIcon;

		std::vector<cocos2d::ui::Button*> menuButtons;
		std::vector<cocos2d::ui::Button*> subButtons;
		std::vector<cocos2d::ui::Slider*> sliderBers;
		std::vector<cocos2d::Label*>	  optionLabels;

		void touchEventOfMainMenu(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
		void touchEventOfSubMenu(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

		void changeToMainWindow();
		void changeToSubWindow();

		void swapWindow(Node* moveOutObj, Node* moveInObj);

		void createMaineMenuWindow();
		void createSubMenuWindow();
		void setOptionWindow();
	};
}

# endif // __UIControl__
