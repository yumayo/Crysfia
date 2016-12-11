#include "LayerWater.h"
#include "LayerFia.h"

USING_NS_CC;

namespace User
{
    LayerWater::LayerWater( )
    {

    }
    LayerWater::~LayerWater( )
    {

    }
    bool LayerWater::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"LayerWater", "res/fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        return true;
    }
    void LayerWater::setup( )
    {
        if ( auto layerFia = getLayer<LayerFia>( ) )
        {
            log( "LayerWater : LayerFia.a[%d]", layerFia->a );
            layerFia->a = 1024;
        }
    }
}
