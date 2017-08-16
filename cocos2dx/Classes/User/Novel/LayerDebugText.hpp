#pragma once
#include "cocos2d.h"
#include "Lib/Utilitys.h"
#include "../LayerBase.h"
#include "SystemLayer.h"
namespace User
{
class LayerDebugText : public LayerBase
{
public:
    static LayerDebugText* create( std::string const& fileName, size_t const& numberOfLine ) \
    { \
        LayerDebugText *pRet = new( std::nothrow ) LayerDebugText( ); \
        if ( pRet && pRet->init( fileName, numberOfLine ) ) \
        { \
            pRet->autorelease( ); \
            return pRet; \
        } \
        else \
        { \
            delete pRet; \
            pRet = nullptr; \
            return nullptr; \
        } \
    }
    bool init( std::string const& fileName, size_t const& numberOfLine )
    {
        auto size = cocos2d::Director::getInstance( )->getVisibleSize( );
        auto scale = cocos2d::Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        setName( "LayerDebugText" );

        if ( auto sprite = cocos2d::Sprite::create( ) )
        {
            sprite->setName( u8"debug_rect" );
            sprite->setTextureRect( cocos2d::Rect( 0, 0, size.width, 64 * scale ) );
            sprite->setPosition( cocos2d::Vec2( 0, 0 ) );
            sprite->setAnchorPoint( cocos2d::Vec2( 0, 0 ) );
            this->addChild( sprite );
        }

        this->removeChildByName( u8"debug_file" );
        if ( auto label = createLabel( fileName ) )
        {
            label->setName( u8"debug_file" );
            label->setAnchorPoint( cocos2d::Vec2( 0, 0 ) );
            label->setPosition( cocos2d::Vec2( 0, 0 ) );
            this->addChild( label );
        }

        this->removeChildByName( u8"debug_line" );
        if ( auto label = createLabel( cocos2d::StringUtils::toString( numberOfLine ) ) )
        {
            label->setName( u8"debug_line" );
            label->setAnchorPoint( cocos2d::Vec2( 1, 0 ) );
            label->setPosition( cocos2d::Vec2( size.width, 0 ) );
            this->addChild( label );
        }
        return true;
    }
    cocos2d::Label * LayerDebugText::createLabel( std::string const & title )
    {
        auto scale = cocos2d::Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        auto font = cocos2d::Label::createWithTTF( title,
                                          u8"res/fonts/HGRGE.TTC",
                                          64 );

        font->setScale( Lib::fitHeight( font, 64 * scale ) );
        font->setTextColor( cocos2d::Color4B( 39, 39, 39, 255 ) );
        return font;
    }
};
}