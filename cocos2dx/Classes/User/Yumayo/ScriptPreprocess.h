# ifndef __ScriptPreprocess__
# define __ScriptPreprocess__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptPreprocess : public ScriptBase
    {
    public:
        ScriptPreprocess();
    public:
        void import( ArgumentList const& args );
        void beginland( ArgumentList const& args );
        void endland( ArgumentList const& args );
    };
}

# endif // __ScriptPreprocess__
