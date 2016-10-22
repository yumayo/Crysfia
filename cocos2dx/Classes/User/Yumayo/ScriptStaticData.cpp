#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    std::map<std::string, ScriptInstruction> ScriptStaticData::data;

    ScriptStaticData::ScriptStaticData( )
    {

    }
    ScriptStaticData::~ScriptStaticData( )
    {

    }
    void ScriptStaticData::runScript( FunctionScriptChip const& functionScriptChip )
    {
        auto itr = data.find( functionScriptChip.variable );
        if ( itr != data.cend( ) )
        {
            itr->second.run( functionScriptChip.functionInfo );
        }
    }
}
