# pragma once

# include "cocos2d.h"
# include "../LayerBase.h"

namespace User
{
    class LayerTutorialBox : public cocos2d::LayerColor
    {
    public:
        CREATE_ARGS_INIT_FUNC( LayerTutorialBox );
        //bool init( ) override;
        //void cleanup( ) override;
    public:
        bool init( std::string const& title, std::function<void( )> const& ok );
        bool remove_started = false;
    };
}