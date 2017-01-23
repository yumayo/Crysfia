# ifndef __SceneTitle__
# define __SceneTitle__

#include "../SceneBase.h"

namespace User
{
    class SceneTitle : public SceneBase
    {
    public:
        SceneTitle( );
        ~SceneTitle( );
        static cocos2d::Scene* create( );
    };
}

# endif // __SceneTitle__
