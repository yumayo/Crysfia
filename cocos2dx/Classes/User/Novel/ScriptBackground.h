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

# endif // __ScriptBackground__
