# ifndef __ScriptItem__
# define __ScriptItem__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptItem : public ScriptBase
    {
    public:
        ScriptItem( cocos2d::Layer* layer, std::string textureName );
        ~ScriptItem( );
    public:
        SCRIPT( get );
    private:
        cocos2d::Sprite* create( );
        std::string textureName;
    };
}

# endif // __ScriptItem__
