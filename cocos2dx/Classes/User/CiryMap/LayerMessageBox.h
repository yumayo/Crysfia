# pragma once

# include "cocos2d.h"
# include "../LayerBase.h"

namespace User
{
    class LayerMessageBox : public cocos2d::LayerColor
    {
    public:
        CREATE_ARGS_INIT_FUNC( LayerMessageBox );
        //bool init( ) override;
        //void cleanup( ) override;
    public:
        bool init( std::string const& message, std::function<void( )> const& ok );
        bool remove_started = false;
    };
}