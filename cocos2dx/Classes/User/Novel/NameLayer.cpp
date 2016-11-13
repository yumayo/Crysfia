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

        return true;
    }
    void NameLayer::setup( )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( 0, 0, visibleSize.width, OptionalValues::lineViewSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        auto pos = origin + Vec2( 0, OptionalValues::lineViewSize + OptionalValues::stringViewSize.y );
        square->setPosition( pos + rect.size / 2 );
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
