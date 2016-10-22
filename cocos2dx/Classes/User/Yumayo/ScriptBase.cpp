#include "ScriptBase.h"

USING_NS_CC;

namespace User
{
    ScriptBase::ScriptBase( )
    {
        
    }
    ScriptBase::~ScriptBase( )
    {
        
    }
    void ScriptBase::run( FunctionInfo const & functionInfo )
    {
        auto itr = functionData.find( functionInfo.name );
        if ( itr != functionData.cend( ) )
        {
            itr->second( functionInfo.argumentList );
        }
    }
}
