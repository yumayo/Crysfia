# ifndef __Home__
# define __Home__

# include "cocos2d.h"
#include "../SceneBase.h"

namespace User
{
	class Home : public SceneBase
	{
	private:

		enum LayerZOders
		{
			DEBUG = 0,
			BACKGROUND,
			PLAYER,
			UI,
		};

	public:
		cocos2d::Scene* create();
	};
}

# endif // __Home__
