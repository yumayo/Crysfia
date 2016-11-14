# ifndef __LayerBase__
# define __LayerBase__

# include "cocos2d.h"

# include <string>

// 可変長配列に対応したcreate関数を作ります。
// 中身はCREATE_FUNCと同じです。
#define CREATE_ARGS_FUNC(__TYPE__) \
template <class... Args> \
static __TYPE__* create(Args... args) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(args...); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

namespace User
{
    class LayerBase : public cocos2d::Layer
    {
    public:
        LayerBase( );
        virtual ~LayerBase( );
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
