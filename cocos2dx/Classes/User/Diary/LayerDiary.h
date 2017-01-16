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
		void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
		std::vector<cocos2d::ui::Button*> menuButton;

		Node* node;
		std::vector<cocos2d::Layer*> layers;

		CREATE_FUNC(LayerDiary);

		int num[15];
    private:		
		
		bool flagDiary;
		int diaryNum;

		std::vector<std::string> name;

		void selectDiary(std::string _name, Node* _tagetNode);
		void setBackground(std::string _filePath);
		void setBackButton(std::string _filePath, cocos2d::Vec2 _pos);
		void setButtons(int _buttonCount);
    };
}

# endif // __LayerDiary__
