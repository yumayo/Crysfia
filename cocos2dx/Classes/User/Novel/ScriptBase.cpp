#include "ScriptBase.h"

USING_NS_CC;

namespace User
{
    ScriptBase::ScriptBase( )
    {

    }
    ScriptBase::ScriptBase( cocos2d::Layer * layer )
        : layer( layer )
    {
    }
    ScriptBase::~ScriptBase( )
    {

    }
    void ScriptBase::run( FunctionInfo const & functionInfo )
    {
        auto itr = funcs.find( functionInfo.name );
        if ( itr != funcs.cend( ) )
        {
            itr->second( functionInfo.argumentList );
        }
    }
}
