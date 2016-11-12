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
		bool init();

		CC_SYNTHESIZE_READONLY(cocos2d::Vec2, winSize, WinSize);
		CC_SYNTHESIZE_READONLY(cocos2d::Vec2, origin, Origin);
		CC_SYNTHESIZE_READONLY(cocos2d::Vec2, pos, Pos);

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
		void changeToDiaryWindow();
		void swapWindow(Node* moveOutObj, Node* moveInObj);

		void createMainMenuWindow();
		void createSubMenuWindow();
		void createDiaryWindow();
		void setOptionWindow();
	};
}

# endif // __UIControl__
