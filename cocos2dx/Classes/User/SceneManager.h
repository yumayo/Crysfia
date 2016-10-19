# ifndef __SceneManager__
# define __SceneManager__

# include "cocos2d.h"

namespace User
{
    class SceneManager
    {
    public:
        static cocos2d::Scene* createTitle( );
    private:
        template<class LayerClass>
        static cocos2d::Layer* createLayer( );
        static void childrenCallSetup( cocos2d::Scene* scene );
    };

    template<class LayerClass>
    inline cocos2d::Layer * SceneManager::createLayer( )
    {
        auto layer = LayerClass::create( );
        layer->setName( typeid( LayerClass ).name( ) );
        return layer;
    }
}

# endif // __SceneManager__
