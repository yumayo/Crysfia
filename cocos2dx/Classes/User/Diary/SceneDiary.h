# ifndef __SceneDiary__
# define __SceneDiary__

# include "cocos2d.h"
#include "../SceneBase.h"
#include "LayerDiary.h"
namespace User
{
    class SceneDiary : public SceneBase
    {
    public:
        SceneDiary( );
        ~SceneDiary( );
        static cocos2d::Scene* create( );
    };
}

# endif // __SceneDiary__
