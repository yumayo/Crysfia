#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    std::map<std::string, std::unique_ptr<ScriptBase>> ScriptStaticData::data;

    void ScriptStaticData::run( FunctionScriptChip const& functionScriptChip )
    {
        auto itr = data.find( functionScriptChip.variable );
        if ( itr != data.cend( ) )
        {
            itr->second->run( functionScriptChip.functionInfo );
        }
    }
    void ScriptStaticData::addData( std::pair<std::string, std::unique_ptr<ScriptBase>>&& pairData )
    {
        data.insert( std::move( pairData ) );
    }
}
