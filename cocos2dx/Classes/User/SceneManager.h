# ifndef __SceneManager__
# define __SceneManager__

# include "cocos2d.h"

# include <string>

namespace User
{
    class SceneManager
    {
    public:
        static void createSystemAppDelegateStart( );
    public:
        static void createSample( );
        static void createTitle( );
        static void createNovel( std::string const& novelPath );
        static void createIslandMap( );
        static void createCiryMap( );
        static void createBreeding( );
    private:
        static void childrenCallSetup( cocos2d::Scene* scene );
        template <class Ty, class... Args>
        static void create( Args... args );
    };

    template<class Ty, class... Args>
    inline void SceneManager::create( Args... args )
    {
        Ty base( args... );
        auto scene = base.create( );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
}

# endif // __SceneManager__
