# ifndef __ScriptName__
# define __ScriptName__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptName : public ScriptBase
    {
    public:
        ScriptName( cocos2d::Layer* layer, std::string characterName );
        ~ScriptName( );
    public:
        void in( ArgumentList const& args );
        void out( ArgumentList const& args );
        void fadein( ArgumentList const& args );
        void fadeout( ArgumentList const& args );
        void slidein( ArgumentList const& args );
        void slideout( ArgumentList const& args );
    private:
        std::string characterName;
    };
}

# endif // __ScriptName__
