#include "ScriptHuman.h"

USING_NS_CC;

namespace User
{
    ScriptHuman::ScriptHuman( cocos2d::Layer* layer, std::string textureName )
        : ScriptBase( layer )
        , texture( Director::getInstance( )->getTextureCache( )->getTextureForKey( textureName ) )
    {
        funcs.insert( std::make_pair( u8"in", [ this ] ( ArgumentList const& args ) { in( args ); } ) );
        funcs.insert( std::make_pair( u8"out", [ this ] ( ArgumentList const& args ) { out( args ); } ) );
        funcs.insert( std::make_pair( u8"fadein", [ this ] ( ArgumentList const& args ) { fadein( args ); } ) );
        funcs.insert( std::make_pair( u8"fadeout", [ this ] ( ArgumentList const& args ) { fadeout( args ); } ) );
        funcs.insert( std::make_pair( u8"slidein", [ this ] ( ArgumentList const& args ) { slidein( args ); } ) );
        funcs.insert( std::make_pair( u8"slideout", [ this ] ( ArgumentList const& args ) { slideout( args ); } ) );
    }
    ScriptHuman::~ScriptHuman( )
    {

    }
    void ScriptHuman::in( ArgumentList const& args )
    {
        layer->removeChildByTag( (int)Tag::Human );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::createWithTexture( texture );
        sprite->setTag( (int)Tag::Human );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );
        layer->addChild( sprite );
    }
    void ScriptHuman::out( ArgumentList const & args )
    {
        layer->removeChildByTag( (int)Tag::Human );
    }
    void ScriptHuman::fadein( ArgumentList const & args )
    {
        layer->removeChildByTag( (int)Tag::Human );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::createWithTexture( texture );
        sprite->setTag( (int)Tag::Human );
        sprite->setOpacity( 0 );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto fade = FadeIn::create( 1.0 );
        sprite->runAction( Sequence::create( fade, nullptr ) );

        layer->addChild( sprite );
    }
    void ScriptHuman::fadeout( ArgumentList const & args )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Human ) )
        {
            auto fade = FadeOut::create( 1.0 );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fade, remove, nullptr ) );
        }
    }
    void ScriptHuman::slidein( ArgumentList const & args )
    {
        layer->removeChildByTag( (int)Tag::Human );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::createWithTexture( texture );
        sprite->setTag( (int)Tag::Human );
        sprite->setOpacity( 0 );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto fade = FadeIn::create( 0.1 );
        auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 100.0F, 0.0F ) ) );
        auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
        sprite->runAction( Spawn::create( fadeWithSlide, nullptr ) );

        layer->addChild( sprite );
    }
    void ScriptHuman::slideout( ArgumentList const & args )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Human ) )
        {
            auto fade = FadeOut::create( 0.1 );
            auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 100.0F, 0.0F ) ) );
            auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fadeWithSlide, remove, nullptr ) );
        }
    }
}
