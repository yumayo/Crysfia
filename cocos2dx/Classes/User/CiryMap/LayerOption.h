# ifndef __LayerOption__
# define __LayerOption__

# include "../LayerBase.h"

#include "ui/CocosGUI.h"

namespace User
{
    class SlideBar : public cocos2d::Node
    {
    public:
        CREATE_ARGS_FUNC( SlideBar );
        SlideBar( );
        SlideBar( float t );
        SlideBar( std::string key );
        std::function<void( float )> move;
        std::function<void( float )> ended;
        cocos2d::ui::Slider* slider;
    private:
        std::string key;
    };

    class LayerOption : public LayerBase
    {
    public:
        CREATE_FUNC( LayerOption );
        LayerOption( );
        ~LayerOption( );
        bool init( ) override;
        void setup( ) override;
    private:
        cocos2d::ui::Button* createBackButton( );
    };
}

# endif // __LayerOption__
