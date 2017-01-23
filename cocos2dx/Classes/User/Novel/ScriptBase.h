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
        virtual ~ScriptBase( );
    public:
        void run( FunctionInfo const& functionInfo );
    protected:
        std::map<std::string, std::function<void( ArgumentList const& )>> funcs;
        cocos2d::Layer* layer = nullptr;
    };
}

# define REGIST_FUNC(class_, func_) funcs.insert( std::make_pair( #func_, std::bind( &class_::func_, this, std::placeholders::_1 ) ) )
# define REGIST_FUNC_NAME(class_, func_, name_) funcs.insert( std::make_pair( name_, std::bind( &class_::func_, this, std::placeholders::_1 ) ) )
# define SCRIPT(name_) void name_( ArgumentList const& args )

# endif // __ScriptBase__
