#include "HumanLayer.h"

USING_NS_CC;

namespace User
{
    HumanLayer::HumanLayer( )
    {

    }
    HumanLayer::~HumanLayer( )
    {

    }
    bool HumanLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        return true;
    }
    void HumanLayer::setup( )
    {

    }
}
