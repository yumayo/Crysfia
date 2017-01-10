# ifndef __LayerDiary__
# define __LayerDiary__

#include "cocos2d.h"
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
		void selectDiary(std::string _name);
		void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
		std::vector<cocos2d::ui::Button*> menuButton;

		Node* node;
		std::vector<cocos2d::Layer*> layers;

		CREATE_FUNC(LayerDiary);

		int num[15];
    private:		
		cocos2d::ui::ListView *listView;
		std::vector<std::string> name;
		bool flagDiary;

    };
}

# endif // __LayerDiary__
