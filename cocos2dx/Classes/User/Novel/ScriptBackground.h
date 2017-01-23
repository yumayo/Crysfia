# ifndef __ScriptBackground__
# define __ScriptBackground__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptBackground : public ScriptBase
    {
    public:
        ScriptBackground( cocos2d::Layer* layer, std::string textureName );
        ~ScriptBackground( );
    public:
        SCRIPT( in );
        SCRIPT( out );
        SCRIPT( fadein );
        SCRIPT( fadeout );
        SCRIPT( circlein );
        SCRIPT( circleout );
    private:
        cocos2d::Sprite* create( );
        std::string textureName;
    };
}

# endif // __ScriptBackground__
