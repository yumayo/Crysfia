#include "ScriptHuman.h"

USING_NS_CC;

namespace User
{
    ScriptHuman::ScriptHuman( cocos2d::Layer* layer, std::string textureName )
        : ScriptBase( layer )
        , textureName( textureName )
    {
        REGIST_FUNC( ScriptHuman, in );
        REGIST_FUNC( ScriptHuman, out );
        REGIST_FUNC( ScriptHuman, fadein );
        REGIST_FUNC( ScriptHuman, fadeout );
    }
    ScriptHuman::~ScriptHuman( )
    {

    }
    SCRIPT( ScriptHuman::in )
    {
        create( );
    }
    SCRIPT( ScriptHuman::out )
    {
        layer->removeChildByTag( (int)Tag::Human );
    }
    SCRIPT( ScriptHuman::fadein )
    {
        auto sprite = create( );
        if ( !sprite ) return;

        sprite->setOpacity( 0 );

        auto fade = FadeIn::create( 1.0 );
        sprite->runAction( Sequence::create( fade, nullptr ) );
    }
    SCRIPT( ScriptHuman::fadeout )
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
