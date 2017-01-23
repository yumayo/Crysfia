# ifndef __ScriptStill__
# define __ScriptStill__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptStill : public ScriptBase
    {
    public:
        ScriptStill( cocos2d::Layer* layer, std::string textureName );
        ~ScriptStill( );
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

# endif // __ScriptStill__
