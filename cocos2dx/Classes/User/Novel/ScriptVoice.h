# ifndef __ScriptVoice__
# define __ScriptVoice__

# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptVoice : public ScriptBase
    {
    public:
        ScriptVoice( cocos2d::Layer* layer, std::string const& dir );
    public:
        SCRIPT( play );
    private:
        std::string dir;
        unsigned int id = 0;
    };
}

# endif // __ScriptVoice__
