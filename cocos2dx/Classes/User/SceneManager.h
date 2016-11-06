# ifndef __SceneManager__
# define __SceneManager__

# include "cocos2d.h"

namespace User
{
    class SceneManager
    {
    public:
        static void createSystemAppDelegateStart( );
    public:
        static void createSample( );
        static void createTitle( );
        static void createYumayo( );
        static void createIslandMap( );
        static void createBreeding( );
    private:
        static void childrenCallSetup( cocos2d::Scene* scene );
        template <typename Ty>
        static void create( );
    };

    template<class Ty>
    inline void SceneManager::create( )
    {
        Ty base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
}

# endif // __SceneManager__
