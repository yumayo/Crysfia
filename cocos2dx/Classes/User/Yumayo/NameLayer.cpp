#include "NameLayer.h"

#include "ScriptName.h"
#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    NameLayer::NameLayer( )
    {

    }
    NameLayer::~NameLayer( )
    {

    }
    bool NameLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        ScriptStaticData::addData( std::make_pair( u8"クロエ名前", std::make_unique<ScriptName>( this, u8"クロエ", u8"F910MinchoW3.otf" ) ) );
        ScriptStaticData::addData( std::make_pair( u8"アレン名前", std::make_unique<ScriptName>( this, u8"アレン", u8"F910MinchoW3.otf" ) ) );

        return true;
    }
    void NameLayer::setup( )
    {
        
    }
}
