# ifndef __ScriptInstruction__
# define __ScriptInstruction__

# include "cocos2d.h"

# include "TextTypes.hpp"
# include "ScriptBase.h"

# include <string>
# include <functional>
# include <map>

namespace User
{
    class ScriptInstruction
    {
    public:
        ScriptInstruction( );
        ~ScriptInstruction( );
    public:
        void run( FunctionInfo const& functionInfo );
    private:
        ScriptBase* data = nullptr;
    };
}

# endif // __ScriptInstruction__
