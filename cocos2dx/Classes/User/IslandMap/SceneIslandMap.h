# ifndef __SceneIslandMap__
# define __SceneIslandMap__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneIslandMap : public SceneBase
    {
    public:
        cocos2d::Scene* create( ) override;
    };
}

# endif // __SceneIslandMap__
