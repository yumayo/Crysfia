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
        static void setup( );
        static void clear( );
        static void run( FunctionScript const& functionScript );
        static void addData( std::pair<std::string, std::unique_ptr<ScriptBase>>&& pairData );
    private:
        static std::map<std::string, std::unique_ptr<ScriptBase>> data;
    };
}

# define REGIST_VARIABLE(variable_, script_) ScriptStaticData::addData( std::make_pair( variable_, std::unique_ptr<ScriptBase>( script_ ) ) );

# endif // __ScriptData__
