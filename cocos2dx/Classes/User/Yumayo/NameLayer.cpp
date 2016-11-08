#include "NameLayer.h"

#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    NameLayer::NameLayer( )
    {

    }
    NameLayer::~NameLayer( )
    {

    }
    bool NameLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        return true;
    }
    void NameLayer::setup( )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( origin.x, origin.y + OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize,
                          visibleSize.width, OptionalValues::fontSize + OptionalValues::lineSpaceSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        square->setPosition( rect.origin + rect.size / 2 );
        this->addChild( square );
    }
    void NameLayer::on( )
    {
        this->setVisible( true );
    }
    void NameLayer::off( )
    {
        this->setVisible( false );
    }
}
