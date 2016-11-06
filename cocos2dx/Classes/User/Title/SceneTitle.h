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
		cocos2d::Scene* create()override;
    private:
    };
}

# endif // __SceneTitle__
