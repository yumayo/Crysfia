# ifndef __SceneBase__
# define __SceneBase__

# include "cocos2d.h"

namespace User
{
    class SceneBase
    {
    public:
        virtual cocos2d::Scene* create( ) = 0;
    protected:
        template<class LayerClass>
        static cocos2d::Layer* createLayer( );
    };

    template<class LayerClass>
    inline cocos2d::Layer * SceneBase::createLayer( )
    {
        auto layer = LayerClass::create( );
        layer->setName( typeid( LayerClass ).name( ) );
        return layer;
    }
}

# endif // __SceneBase__
