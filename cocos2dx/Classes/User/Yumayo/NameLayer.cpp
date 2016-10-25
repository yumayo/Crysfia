#include "NameLayer.h"

#include "ScriptName.h"
#include "ScriptStaticData.h"
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

        ScriptStaticData::addData( std::make_pair( u8"クロエ名前", std::make_unique<ScriptName>( this, u8"クロエ", u8"F910MinchoW3.otf" ) ) );
        ScriptStaticData::addData( std::make_pair( u8"アレン名前", std::make_unique<ScriptName>( this, u8"アレン", u8"F910MinchoW3.otf" ) ) );

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
}
