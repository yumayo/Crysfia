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
        static void run( FunctionScript const& functionScript );
        static void addData( std::pair<std::string, std::unique_ptr<ScriptBase>>&& pairData );
    private:
        static cocos2d::Scene* scene;
        static std::map<std::string, std::unique_ptr<ScriptBase>> data;
    };
}

# endif // __ScriptData__
