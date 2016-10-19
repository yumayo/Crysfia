# ifndef __SceneManager__
# define __SceneManager__

# include "cocos2d.h"

namespace User
{
    class SceneManager
    {
    public:
        static void createSystemAppDelegateStart( );
        static void createSample( );
    private:
        static void childrenCallSetup( cocos2d::Scene* scene );
    };
}

# endif // __SceneManager__
