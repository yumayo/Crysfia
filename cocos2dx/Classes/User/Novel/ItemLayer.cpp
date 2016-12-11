#include "ItemLayer.h"

#include "../../Lib/Utility/Utilitys.h"

#include "NovelLayer.h"

USING_NS_CC;

namespace User
{
    ItemLayer::ItemLayer( )
    {

    }
    ItemLayer::~ItemLayer( )
    {

    }
    bool ItemLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        return true;
    }
    void ItemLayer::setup( )
    {
        novelLayer = getLayer<NovelLayer>( );
    }
    void ItemLayer::make( std::string const & name )
    {
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto lay = LayerColor::create( Color4B::BLACK, vs.width, vs.height );
        lay->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
        lay->setOpacity( 0 );
        lay->runAction( FadeTo::create( 0.3F, 128 ) );
        addChild( lay );

        auto event = GetItemEvent::create( )->make( name );
        addChild( event );
        event->setOnExitCallback( [ this, lay ]
        {
            lay->runAction( Sequence::create( FadeOut::create( 0.3F ), RemoveSelf::create( ), nullptr ) );
            if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->delayOn( );
        } );
        if ( novelLayer ) novelLayer->pause( );
    }
    GetItemEvent * GetItemEvent::make( std::string const& name )
    {
        UserDefault::getInstance( )->setBoolForKey( name.c_str( ), true );

        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        initWithFile( u8"res/Image/WindowBase/WinBase_58.png",
                      Rect( 0 * scale, 0 * scale,
                            120 * scale, 120 * scale ),
                      Rect( 32 * scale, 32 * scale,
                            64 * scale, 64 * scale ) );

        auto content_size = Size( 640, 640 ) / scale;
        setContentSize( content_size );
        setPosition( vo + vs * 0.5 );

        {
            auto effect = GetItemEffect::create( )->make( );
            addChild( effect );
            auto s = effect->getContentSize( );
            effect->setScale( Lib::fitWidth( effect, content_size.width * 0.8 ), Lib::fitWidth( effect, content_size.width * 0.8 ) );
            effect->setPosition( Vec2( content_size.width * 0.5, content_size.height - s.height * Lib::fitWidth( effect, content_size.width * 0.8 ) ) );
            effect->setAnchorPoint( Vec2( 0.5, 1 ) );
        }


        auto item = Sprite::create( u8"res/texture/item/" + name + u8".png" );
        auto pixel = item->getContentSize( ) / scale;
        item->setScale( 10 );
        item->setOpacity( 0 );
        item->setPosition( content_size / 2 );

        //TIPS:128��scale���|���ĂȂ��̂́A�e�̃I�u�W�F�N�g��ContentSize�ɃX�P�[�����������ĂȂ�����ł��B
        auto scale_animation = EaseCubicActionOut::create( ScaleTo::create( 1.0F, Lib::fitHeight( this, 128 ) ) );
        auto rotate_animation = EaseCubicActionOut::create( RotateBy::create( 1.0F, 360 ) );
        auto fade_animation = EaseCubicActionOut::create( FadeIn::create( 1.0F ) );
        auto begin_animation = Spawn::create( scale_animation, rotate_animation, fade_animation, nullptr );
        auto up = EaseSineIn::create( ScaleTo::create( 0.25F, Lib::fitHeight( this, 128 * 2.0F ) ) );
        auto down = EaseSineOut::create( ScaleTo::create( 0.25F, Lib::fitHeight( this, 128 * 1.0F ) ) );
        auto powan_animation = Sequence::create( up, down, nullptr );

        auto createButton = CallFunc::create( [ this, scale ]
        {
            auto button = ui::Button::create( u8"res/texture/item/effect/back.png" );
            addChild( button );
            button->setScale( Lib::fitWidth( button, 128 / scale ), Lib::fitWidth( button, 128 / scale ) );
            button->setPosition( Vec2( getContentSize( ).width * 0.5, 128 / scale ) );
            button->setOpacity( 0 );
            button->runAction( FadeIn::create( 0.3F ) );
            button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::ENDED )
                {
                    removeFromParentAndCleanup( true );
                }
            } );
        } );

        item->runAction( Sequence::create( begin_animation, createButton, powan_animation, nullptr ) );
        addChild( item );

        return this;
    }
    GetItemEffect * GetItemEffect::make( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        std::vector<std::string> names = { u8"�A", u8"�C", u8"�e", u8"��", u8"�Q", u8"�b", u8"�g" };


        auto effect_width_size = 1000.0F;
        auto one_effect_width_size = effect_width_size / names.size( );
        setContentSize( Size( effect_width_size, one_effect_width_size ) );
        setAnchorPoint( Vec2( 0.5, 0.5 ) );

        float i = 0;
        for ( auto& name : names )
        {
            auto sprite = Sprite::create( u8"res/texture/item/effect/" + name + u8".png" );
            sprite->setPosition( Vec2( i * one_effect_width_size, 0 ) );
            sprite->setScale( Lib::fitWidth( sprite, one_effect_width_size ), Lib::fitWidth( sprite, one_effect_width_size ) );
            sprite->setAnchorPoint( Vec2( 0, 0 ) );
            addChild( sprite );

            auto up = EaseSineIn::create( MoveTo::create( 0.25F, Vec2( i * one_effect_width_size, one_effect_width_size ) ) );
            auto down = EaseSineIn::create( MoveTo::create( 0.25F, Vec2( i * one_effect_width_size, 0 ) ) );
            auto delay = DelayTime::create( i * 0.2F );

            sprite->runAction( Sequence::create( delay, up, down, nullptr ) );

            i += 1.0F;
        }

        return this;
    }
}