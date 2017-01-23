# ifndef __ScriptName__
# define __ScriptName__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptName : public ScriptBase
    {
    public:
        ScriptName( cocos2d::Layer* layer, std::string characterName, std::string fontPath );
        ~ScriptName( );
    public:
        SCRIPT( in );
        SCRIPT( out );
    private:
        cocos2d::Label* create( );
    private:
        std::string characterName;
        std::string fontPath;
        cocos2d::Vec2 position;
        float slideSize;
    };
}

# endif // __ScriptName__
