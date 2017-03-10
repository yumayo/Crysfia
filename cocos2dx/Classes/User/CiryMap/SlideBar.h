# ifndef __SlideBar__
# define __SlideBar__

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
}

# endif // __SlideBar__
