# ifndef __ScriptData__
# define __ScriptData__

# include "cocos2d.h"

# include "TextTypes.hpp"
# include "ScriptBase.h"

# include <map>
# include <string>
# include <memory>

namespace User
{
    class ScriptStaticData
    {
    public:
        ScriptStaticData( cocos2d::Scene* scene );
        ~ScriptStaticData( );
    public:
        static void run( FunctionScriptChip const& functionScriptChip );
    private:
        static cocos2d::Scene* scene;
        static std::map<std::string, std::shared_ptr<ScriptBase>> data;
    };
}

# endif // __ScriptData__
