# ifndef __Scene_ishibashi__
# define __Scene_ishibashi__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
	class Scene_ishibashi : public SceneBase
	{
	public:
		cocos2d::Scene* create() override;
	};
}

# endif // __Scene_ishibashi__