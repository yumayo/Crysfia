#include "LayerTy.h"

USING_NS_CC;

namespace User
{
    LayerTy::LayerTy( )
    {

    }
    LayerTy::~LayerTy( )
    {
    }
    bool LayerTy::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        return true;
    }
    void LayerTy::setup( )
    {

    }
    void LayerTy::update( float delta )
    {

    }
}
