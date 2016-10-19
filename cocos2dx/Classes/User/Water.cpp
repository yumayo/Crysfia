#include "Water.h"
#include "Fia.h"

USING_NS_CC;

namespace User
{
    Water::Water( )
    {

    }
    Water::~Water( )
    {

    }
    bool Water::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"Water", "fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        return true;
    }
    void Water::setup( )
    {
        if ( auto fia = getLayer<Fia>( ) )
        {
            log( "Water : Fia.a[%d]", fia->a );
            fia->a = 1024;
        }
    }
}
