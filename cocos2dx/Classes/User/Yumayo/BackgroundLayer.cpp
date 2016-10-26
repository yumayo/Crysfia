#include "BackgroundLayer.h"

USING_NS_CC;

namespace User
{
    BackgroundLayer::BackgroundLayer( )
    {

    }
    BackgroundLayer::~BackgroundLayer( )
    {

    }
    bool BackgroundLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        return true;
    }
    void BackgroundLayer::setup( )
    {

    }
}
