#include "SelectLayer.h"

USING_NS_CC;

namespace User
{
    SelectLayer::SelectLayer( )
    {

    }
    SelectLayer::~SelectLayer( )
    {

    }
    bool SelectLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        return true;
    }
    void SelectLayer::setup( )
    {

    }
}
