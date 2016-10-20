# ifndef __ScriptData__
# define __ScriptData__

# include "cocos2d.h"

# include "TextTypes.hpp"
# include "ScriptInstruction.h"

# include <map>
# include <string>

namespace User
{
    class ScriptStaticData
    {
    public:
        ScriptStaticData( );
        ~ScriptStaticData( );
    public:
        static void runScript( FunctionScriptChip const& functionScriptChip );
    private:
        static std::map<std::string, ScriptInstruction> data;
    };
}

# endif // __ScriptData__
