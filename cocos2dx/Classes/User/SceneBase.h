# ifndef __SceneBase__
# define __SceneBase__

# include "cocos2d.h"

namespace User
{
    class SceneBase : public cocos2d::Scene
    {
    public:
        virtual ~SceneBase( );
    protected:
        template<class LayerClass>
        static cocos2d::Layer* createLayer( );
        template<class LayerClass, class... Args>
        static cocos2d::Layer* createLayer( Args... args );
    };

    template<class LayerClass>
    inline cocos2d::Layer * SceneBase::createLayer( )
    {
        auto layer = LayerClass::create( );
        layer->setName( typeid( LayerClass ).name( ) );
        return layer;
    }
    template<class LayerClass, class ...Args>
    inline cocos2d::Layer * SceneBase::createLayer( Args ...args )
    {
        auto layer = LayerClass::create( args... );
        layer->setName( typeid( LayerClass ).name( ) );
        return layer;
    }
}

# endif // __SceneBase__
