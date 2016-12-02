# ifndef __Home__
# define __Home__

# include "cocos2d.h"
#include "../SceneBase.h"

namespace User
{
	class SceneBreeding : public SceneBase
	{
	public:
		SceneBreeding();
		cocos2d::Scene* create()override;
	};
}

# endif // __Home__
