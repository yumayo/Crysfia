#include "BackgroundLayer.h"

#include "ScriptBackground.h"
#include "ScriptStaticData.h"

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

        addTexture( "forest.jpg" );
        ScriptStaticData::addData( std::make_pair( u8"êXâÊëú", std::make_unique<ScriptBackground>( this, u8"forest.jpg" ) ) );

        return true;
    }
    void BackgroundLayer::setup( )
    {

    }
    void BackgroundLayer::addTexture( std::string texturePath )
    {
        Director::getInstance( )->getTextureCache( )->addImage( "res/texture/" + texturePath );
    }
}
