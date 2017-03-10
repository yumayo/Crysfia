# ifndef __ScriptHuman__
# define __ScriptHuman__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptHuman : public ScriptBase
    {
    public:
        ScriptHuman( cocos2d::Layer* layer, std::string textureName );
        ~ScriptHuman( );
    public:
        SCRIPT( in );
        SCRIPT( out );
        SCRIPT( fadein );
        SCRIPT( fadeout );
    private:
        cocos2d::Sprite* create( );
        std::string textureName;
    };
}

# endif // __ScriptHuman__
