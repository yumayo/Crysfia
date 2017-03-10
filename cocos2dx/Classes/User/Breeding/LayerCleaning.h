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
		void update(float dt);

		bool isFinish = false;
	private:

		int  cleanDegrees;
		bool canCleaning;

		bool init();
		void thisLocationTouchProcess();
		void uiTouchProcess();

		void setInfoLayer();
		void setInfoLayer(cocos2d::Node* _node, cocos2d::Label* _label, std::string _text, int _fontSize = 24);
		
		void labelAction(float dt);
		void completeDirection();

		cocos2d::Size			winSize;
		cocos2d::Vec2			touchLocation;

		cocos2d::Sprite*		bottle;
		cocos2d::Sprite*		mask;
		cocos2d::Sprite*		clippingShape;
		cocos2d::Sprite*		bottleTexture;

		cocos2d::ClippingNode*	clippingNode;
		cocos2d::Label*			infoLabel;
		cocos2d::Sequence*		testAction;

		cocos2d::EventListenerTouchOneByOne*	listener;
		std::vector<cocos2d::ui::Button*>		buttons;
	};
}

# endif // __LayerCleaning__
