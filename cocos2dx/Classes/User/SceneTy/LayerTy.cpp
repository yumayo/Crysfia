#include "LayerTy.h"

#include "SampleLive2DSprite.h"

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

        auto pLive2DSprite = SampleLive2DSprite::createDrawNode( );
        this->addChild( pLive2DSprite );

        return true;
    }
    void LayerTy::setup( )
    {

    }
    void LayerTy::update( float delta )
    {

    }
}
