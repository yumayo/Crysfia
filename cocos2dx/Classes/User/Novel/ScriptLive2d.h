# ifndef __ScriptLive2d__
# define __ScriptLive2d__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptLive2d : public ScriptBase
    {
    public:
        ScriptLive2d( cocos2d::Layer* layer, std::string model, std::string dir );
        ~ScriptLive2d( );
    public:
        SCRIPT( in );
        SCRIPT( out );
    public:
        // 表情に関わるスクリプトです。
        SCRIPT( normal );
        SCRIPT( rejoice );
        SCRIPT( sorrow );
        SCRIPT( getSurprise );
        SCRIPT( getAngry );
        SCRIPT( 真面目な顔 );
        SCRIPT( 悩んでる顔 );
    public:
        SCRIPT( touchon );
        SCRIPT( touchoff );
    private:
        cocos2d::Node* node = nullptr;
    };
}

# endif // __ScriptLive2d__
