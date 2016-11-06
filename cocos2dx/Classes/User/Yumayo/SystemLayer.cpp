#include "SystemLayer.h"

#include "ScriptSystem.h"
#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    SystemLayer::SystemLayer( )
    {

    }
    SystemLayer::~SystemLayer( )
    {

    }
    bool SystemLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        auto script = new ScriptSystem( this );
        ScriptStaticData::addData( std::make_pair( u8"sys", std::unique_ptr<ScriptBase>(script) ) );

        return true;
    }
    void SystemLayer::setup( )
    {
        ScriptStaticData::run( { u8"sys", u8"SETUP" } );
    }
}
