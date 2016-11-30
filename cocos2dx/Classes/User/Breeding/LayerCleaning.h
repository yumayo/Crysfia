# ifndef __LayerCleaning__
# define __LayerCleaning__

# include "cocos2d.h"
#include "VariousStatus.h"
#include "../LayerBase.h"
#include "ui/CocosGUI.h"

namespace User
{
	class LayerCleaning : public LayerBase
	{
	public:
		CREATE_FUNC(LayerCleaning);
		LayerCleaning();
		~LayerCleaning();
	private:

		bool init();
		void thisLocationTouchProcess();
		void uiTouchProcess();
		void hoge();

		cocos2d::Size			winSize;
		cocos2d::Sprite*		bottle;
		cocos2d::Sprite*		mask;
		cocos2d::ClippingNode*	clippingNode;
		cocos2d::Sprite*		clippingShape;

		std::vector<cocos2d::ui::Button*> buttons;
	};
}

# endif // __LayerCleaning__
