# ifndef __LayerBase__
# define __LayerBase__

# include "cocos2d.h"

# include <string>

namespace User
{
    class LayerBase : public cocos2d::Layer
    {
    public:
        LayerBase( );
        ~LayerBase( );
        // init関数の後に呼ばれます。
        // setupからgetLayerが使えるようになります。
        virtual void setup( );
    public:
        // この関数でシーンに追加されている全てのレイヤーにアクセスできます。
        template<class LayerClass>
        LayerClass* getLayer( );
    };

    template<class LayerClass>
    inline LayerClass* LayerBase::getLayer( )
    {
        auto scene = this->getScene( );
        auto node = scene->getChildByName( typeid( LayerClass ).name( ) );
        return dynamic_cast<LayerClass*>( node );
    }
}

# endif // __SceneBase__
