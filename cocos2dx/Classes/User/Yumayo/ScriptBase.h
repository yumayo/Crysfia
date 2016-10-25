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
        ScriptBase( cocos2d::Layer* layer );
        ~ScriptBase( );
    public:
        void run( FunctionInfo const& functionInfo );
    protected:
        std::map<std::string, std::function<void( ArgumentList const& )>> funcs;
        cocos2d::Layer* layer = nullptr;
    };
}

# endif // __ScriptBase__
