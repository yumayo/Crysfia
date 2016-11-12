#include "StillLayer.h"

USING_NS_CC;

namespace User
{
    StillLayer::StillLayer( )
    {

    }
    StillLayer::~StillLayer( )
    {

    }
    bool StillLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        return true;
    }
    void StillLayer::setup( )
    {

    }
}
