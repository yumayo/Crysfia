# ifndef __ScriptSystem__
# define __ScriptSystem__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptSystem : public ScriptBase
    {
    public:
        ScriptSystem( cocos2d::Layer* layer );
        ~ScriptSystem( );
    public:
        void line( ArgumentList const& args );
        void name( ArgumentList const& args );
    public:
        static size_t novelIndex;
    };
}

# endif // __ScriptSystem__
