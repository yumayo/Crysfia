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
        void in( ArgumentList const& args );
        void out( ArgumentList const& args );
        void fadein( ArgumentList const& args );
        void fadeout( ArgumentList const& args );
        void slidein( ArgumentList const& args );
        void slideout( ArgumentList const& args );
    private:
        cocos2d::Texture2D* texture;
    };
}

# endif // __ScriptHuman__
