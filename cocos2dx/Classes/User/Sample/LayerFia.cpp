#include "LayerFia.h"
#include "LayerWater.h"

USING_NS_CC;

namespace User
{
    LayerFia::LayerFia( )
    {

    }
    LayerFia::~LayerFia( )
    {

    }
    bool LayerFia::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"LayerFia", "res/fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        return true;
    }
    void LayerFia::setup( )
    {
        if ( auto layerWater = getLayer<LayerWater>( ) )
        {
            log( "LayerFia : LayerWater.a[%d]", layerWater->a );
        }
    }
}
