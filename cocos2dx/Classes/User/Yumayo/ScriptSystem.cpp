#include "ScriptSystem.h"

USING_NS_CC;

namespace User
{
    size_t ScriptSystem::novelIndex = 0;

    ScriptSystem::ScriptSystem( )
    {
        funcs.insert( std::make_pair( u8"l", [ this ] ( ArgumentList const& args ) { line( args ); } ) );
    }
    ScriptSystem::~ScriptSystem( )
    {

    }
    void ScriptSystem::line( ArgumentList const& args )
    {
        novelIndex = lineSize;
    }
    void ScriptSystem::name( ArgumentList const & args )
    {

    }
}
