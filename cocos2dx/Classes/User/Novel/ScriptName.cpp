#include "ScriptName.h"

#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    ScriptName::ScriptName( cocos2d::Layer* layer, std::string characterName, std::string fontPath )
        : ScriptBase( layer )
        , characterName( characterName )
        , fontPath( fontPath )
        , position( )
        , slideSize( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        position = origin + Vec2( 0, OptionalValues::lineViewSize + OptionalValues::stringViewSize.y + OptionalValues::lineViewSize );
        slideSize = visibleSize.width * 0.1;

        REGIST_SCRIPT( u8"in", ScriptName::in );
        REGIST_SCRIPT( u8"out", ScriptName::out );
    }
    ScriptName::~ScriptName( )
    {

    }
    void ScriptName::in( ArgumentList const& args )
    {
        auto label = create( );
        if ( !label ) return;

        label->setOpacity( 0 );

        auto fade = FadeIn::create( 0.1 );
        auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( slideSize, 0.0F ) ) );
        auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
        label->runAction( Spawn::create( fadeWithSlide, nullptr ) );
    }
    void ScriptName::out( ArgumentList const & args )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Name ) )
        {
            auto fade = FadeOut::create( 0.1 );
            auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( slideSize, 0.0F ) ) );
            auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fadeWithSlide, remove, nullptr ) );
        }
    }
    cocos2d::Label * ScriptName::create( )
    {
        layer->removeChildByTag( (int)Tag::Name );

        auto label = Label::createWithTTF( characterName, "res/fonts/" + fontPath, OptionalValues::fontSize );
        if ( !label ) return nullptr;

        label->setTag( (int)Tag::Name );
        label->setPosition( position + Vec2( slideSize, -label->getContentSize( ).height ) );
        layer->addChild( label );

        return label;
    }
}
