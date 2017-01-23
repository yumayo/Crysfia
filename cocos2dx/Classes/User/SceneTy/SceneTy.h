# ifndef __SceneTy__
# define __SceneTy__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneTy : public SceneBase
    {
    public:
        cocos2d::Scene* create( );
    };
}

# endif // __SceneTy__
