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
        static void createCiryMap( std::string const& backgroundPath );
        static void createBreeding( );
		static void createCloset();
		static void createCreaning();
    private:
        static void childrenCallSetup( cocos2d::Scene* scene );
        template <class Ty>
        static void create( );
        template <class Ty, class... Args>
        static void create( Args... args );
        template <class Ty, class TyTranstion, class ...TyTranstionArgs>
        static void create( TyTranstionArgs... tyTranstionArgs );
    };

    template<class Ty>
    inline void SceneManager::create( )
    {
        Ty base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
    template<class Ty, class... Args>
    inline void SceneManager::create( Args... args )
    {
        auto scene = Ty::create( args... );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
    template<class Ty, class TyTranstion, class ...TyTranstionArgs>
    inline void SceneManager::create( TyTranstionArgs... tyTranstionArgs )
    {
        Ty base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        auto transtion = TyTranstion::create( tyTranstionArgs..., scene );

        cocos2d::Director::getInstance( )->replaceScene( transtion );
    }
}

# endif // __SceneManager__
