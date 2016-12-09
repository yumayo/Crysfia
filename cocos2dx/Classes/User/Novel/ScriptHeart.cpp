#include "ScriptHeart.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "INIWriter.h"

USING_NS_CC;

namespace User
{
    HeartGauge* HeartGauge::make( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        {
            auto size = Director::getInstance( )->getVisibleSize( );
            auto origin = Director::getInstance( )->getVisibleOrigin( );
            setPosition( origin + Vec2( 0, size.height ) );
        }

        auto anchor = Vec2( 0, 1 );
        if ( auto frame = Sprite::create( u8"res/texture/system/heart.frame.png" ) )
        {
            addChild( frame, 1 );
            auto frameSize = frame->getContentSize( );
            setContentSize( frameSize );
            frame->setAnchorPoint( anchor );

            size = frame->getTexture( )->getContentSizeInPixels( );
        }

        now = UserDefault::getInstance( )->getIntegerForKey( u8"親愛度" );
        start = 7;
        end = size.width - 9;

        if ( auto clipping = ClippingNode::create( ) )
        {
            addChild( clipping );
            clipping->setInverted( false );
            clipping->setAlphaThreshold( 0.0 );

            if ( auto mask = Sprite::create( "res/texture/system/heart.mask.png" ) )
            {
                clipping->setStencil( mask );
                mask->setAnchorPoint( anchor );
            }

            if ( auto background = Sprite::create( u8"res/texture/system/favoritegauge.png",
                                                   Rect( 0, 0, ( start + getWidth( now ) ) * scale, size.height * scale ) ) )
            {
                this->background = background;
                clipping->addChild( background );
                background->setAnchorPoint( anchor );
                background->getTexture( )->setTexParameters( { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT } );
            }
        }

        return this;
    }

    HeartGauge* HeartGauge::scriptUpAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( value ) );
        setScale( 0.5, 0.5 );
        return this;
    }

    HeartGauge* HeartGauge::scriptDownAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( -value ) );
        setScale( 0.5, 0.5 );
        return this;
    }

    HeartGauge * HeartGauge::up( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( value ) );
        return this;
    }

    HeartGauge * HeartGauge::down( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( -value ) );
        return this;
    }

    int HeartGauge::getWidth( int value )
    {
        float t = value;
        return ( end - start ) * ( t / max );
    }

    cocos2d::FiniteTimeAction * HeartGauge::createValueAction( int value )
    {
        if ( !background ) return nullptr;

        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        return CallFunc::create( [ this, value, scale ]
        {
            auto targetValue = clampf( now + value, 0, max );

            UserDefault::getInstance( )->setIntegerForKey( u8"親愛度", targetValue );
            auto rect = background->getTextureRect( );
            background->runAction( ActionFloat::create( 1.0F, now, targetValue, [ = ] ( float t )
            {
                background->setTextureRect( Rect( rect.origin.x, rect.origin.y, ( start + getWidth( t ) ) * scale, rect.size.height ) );
            } ) );

            now = targetValue;
        } );
    }

    cocos2d::Sequence* HeartGauge::createInValueStopOutExitAction( int value )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        auto pixel = size / scale;
        setPosition( getPosition( ) + Vec2( 0, pixel.height ) * scale );
        auto movein = EaseExponentialOut::create( MoveBy::create( 0.5, Vec2( 0, -pixel.height ) * scale ) );
        auto moveout = EaseExponentialOut::create( MoveBy::create( 0.5, Vec2( 0, pixel.height ) * scale ) );

        auto stop = DelayTime::create( 2.0F );
        auto exit = RemoveSelf::create( );

        if ( auto action = createValueAction( value ) )
        {
            return Sequence::create( movein, action, stop, moveout, exit, nullptr );
        }
        return nullptr;
    }

    ScriptHeart::ScriptHeart( cocos2d::Layer * layer )
        : ScriptBase( layer )
    {
        REGIST_FUNC( ScriptHeart, up );
        REGIST_FUNC( ScriptHeart, down );
    }
    SCRIPT( ScriptHeart::up )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            if ( auto heart = HeartGauge::create( )->make( )->scriptUpAction( args[0] ) )
            {
                layer->addChild( heart );
            }
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptHeart::down )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            if ( auto heart = HeartGauge::create( )->make( )->scriptDownAction( args[0] ) )
            {
                layer->addChild( heart );
            }
        }
        break;
        default:
            break;
        }
    }
}
