#include "ScriptHuman.h"

USING_NS_CC;

namespace User
{
    ScriptHuman::ScriptHuman( cocos2d::Layer* layer, std::string textureName )
        : ScriptBase( layer )
        , textureName( textureName )
    {
        REGIST_SCRIPT( u8"in", ScriptHuman::in );
        REGIST_SCRIPT( u8"out", ScriptHuman::out );
        REGIST_SCRIPT( u8"fadein", ScriptHuman::fadein );
        REGIST_SCRIPT( u8"fadeout", ScriptHuman::fadeout );
    }
    ScriptHuman::~ScriptHuman( )
    {

    }
    void ScriptHuman::in( ArgumentList const& args )
    {
        create( );
    }
    void ScriptHuman::out( ArgumentList const & args )
    {
        layer->removeChildByTag( (int)Tag::Human );
    }
    void ScriptHuman::fadein( ArgumentList const & args )
    {
        auto sprite = create( );
        if ( !sprite ) return;

        sprite->setOpacity( 0 );

        auto fade = FadeIn::create( 1.0 );
        sprite->runAction( Sequence::create( fade, nullptr ) );
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
    cocos2d::Sprite * ScriptHuman::create( )
    {
        layer->removeChildByTag( (int)Tag::Human );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return nullptr;

        sprite->setTag( (int)Tag::Human );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );
        layer->addChild( sprite );

        return sprite;
    }
}
