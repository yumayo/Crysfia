#include "ScriptPreprocess.h"

USING_NS_CC;

namespace User
{
    ScriptPreprocess::ScriptPreprocess( )
        : ScriptBase( )
    {
        funcs.insert( std::make_pair( u8"import", [ this ] ( ArgumentList const& args ) { import( args ); } ) );
        funcs.insert( std::make_pair( u8"beginland", [ this ] ( ArgumentList const& args ) { beginland( args ); } ) );
        funcs.insert( std::make_pair( u8"endland", [ this ] ( ArgumentList const& args ) { endland( args ); } ) );
    }
    void ScriptPreprocess::import( ArgumentList const & args )
    {
        if ( args.size( ) == 1 )
        {
            TextData textData;
            textData.makeData( args[0] );
            chunk.back( ).insert( chunk.back( ).cend( ), textData.chunk.back( ).cbegin( ), textData.chunk.back( ).cend( ) );
        };
    }
    void ScriptPreprocess::beginland( ArgumentList const & args )
    {
    }
    void ScriptPreprocess::endland( ArgumentList const & args )
    {
    }
}
