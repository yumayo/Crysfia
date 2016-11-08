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
        void in( ArgumentList const& args );
        void out( ArgumentList const& args );
        void fadein( ArgumentList const& args );
        void fadeout( ArgumentList const& args );
        void circlein( ArgumentList const& args );
        void circleout( ArgumentList const& args );
    private:
        cocos2d::Sprite* create( );
        std::string textureName;
    };
}

# endif // __ScriptStill__
