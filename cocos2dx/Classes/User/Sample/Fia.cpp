#include "Fia.h"
#include "Water.h"

USING_NS_CC;

namespace User
{
    Fia::Fia( )
    {

    }
    Fia::~Fia( )
    {

    }
    bool Fia::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"Fia", "fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        return true;
    }
    void Fia::setup( )
    {
        if ( auto water = getLayer<Water>( ) )
        {
            log( "Fia : Water.a[%d]", water->a );
        }
    }
}
