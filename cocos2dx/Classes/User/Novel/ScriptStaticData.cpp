#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    std::map<std::string, std::unique_ptr<ScriptBase>> ScriptStaticData::data;

    void ScriptStaticData::setup( )
    {
        clear( );
    }
    void ScriptStaticData::clear( )
    {
        data.clear( );
    }
    void ScriptStaticData::run( FunctionScript const& functionScript )
    {
        auto itr = data.find( functionScript.variable );
        if ( itr != data.cend( ) )
        {
            itr->second->run( functionScript.functionInfo );
        }
    }
    void ScriptStaticData::addData( std::pair<std::string, std::unique_ptr<ScriptBase>>&& pairData )
    {
        data.insert( std::move( pairData ) );
    }
}
