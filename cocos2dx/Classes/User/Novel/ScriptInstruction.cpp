#include "ScriptInstruction.h"

USING_NS_CC;

namespace User
{
    ScriptInstruction::ScriptInstruction( )
    {
        
    }
    ScriptInstruction::~ScriptInstruction( )
    {
        
    }
    void ScriptInstruction::run( FunctionInfo const & functionInfo )
    {
        data->run( functionInfo );
    }
}
