# ifndef __SceneSample__
# define __SceneSample__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneSample : public SceneBase
    {
    public:
        cocos2d::Scene* create( ) override;
    };
}

# endif // __SceneSample__
