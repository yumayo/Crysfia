# ifndef __ScriptBase__
# define __ScriptBase__

# include "cocos2d.h"

# include <map>
# include <string>
# include <functional>

# include "TextTypes.hpp"

namespace User
{
    class ScriptBase
    {
    public:
        ScriptBase( );
        ~ScriptBase( );
    public:
        void run( FunctionInfo const& functionInfo );
    protected:
        std::map<std::string, std::function<void( ArgumentList const& )>> functionData;
    };
}

# endif // __ScriptBase__
