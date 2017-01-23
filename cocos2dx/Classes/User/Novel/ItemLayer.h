# ifndef __ItemLayer__
# define __ItemLayer__

# include "../LayerBase.h"
# include "ui/CocosGUI.h"

namespace User
{
    class ItemLayer : public LayerBase
    {
    public:
        CREATE_FUNC( ItemLayer );
        ItemLayer( );
        ~ItemLayer( );
        bool init( ) override;
        void setup( ) override;
        void make( std::string const& name );
    private:
        bool item = false;
        cocos2d::Layer* novelLayer = nullptr;
    };

    class GetItemEvent : public cocos2d::ui::Scale9Sprite
    {
    public:
        CREATE_FUNC( GetItemEvent );
        GetItemEvent* make( std::string const& name );
    };

    class GetItemEffect : public cocos2d::Node
    {
    public:
        CREATE_FUNC( GetItemEffect );
        GetItemEffect* make( );
    };
}

# endif // __ItemLayer__
