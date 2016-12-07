#include "ScriptHeart.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "INIWriter.h"

USING_NS_CC;

namespace User
{
    HeartGauge* HeartGauge::make( )
    {
        now = UserDefault::getInstance( )->getIntegerForKey( u8"親愛度" );
        size = Size( 512, 196 ) * 0.75;
        start = 81.0F / 2;
        end = size.width - start;

        {
            auto size = Director::getInstance( )->getVisibleSize( );
            auto origin = Director::getInstance( )->getVisibleOrigin( );
            setPosition( origin + Vec2( 0, size.height ) );
        }

        auto anchor = Vec2( 0, 1 );

        if ( auto clipping = ClippingNode::create( ) )
        {
            addChild( clipping );
            clipping->setInverted( false );
            clipping->setAlphaThreshold( 0.0 );

            if ( auto mask = Sprite::create( "res/texture/system/frame.mask.png" ) )
            {
                clipping->setStencil( mask );
                auto maskSize = mask->getContentSize( );
                mask->setAnchorPoint( anchor );
                mask->setScale( size.width / maskSize.width, size.height / maskSize.height );
            }

            if ( auto background = Sprite::create( u8"res/texture/system/favoritegauge.jpg",
                                                   Rect( 0, 0, start + getWidth( now ), size.height ) ) )
            {
                this->background = background;
                clipping->addChild( background );
                background->setAnchorPoint( anchor );
                background->getTexture( )->setTexParameters( { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT } );
            }
        }

        if ( auto frame = Sprite::create( u8"res/texture/system/frame.png" ) )
        {
            addChild( frame );
            auto frameSize = frame->getContentSize( );
            frame->setAnchorPoint( anchor );
            frame->setScale( size.width / frameSize.width, size.height / frameSize.height );
        }

        return this;
    }

    HeartGauge* HeartGauge::scriptUpAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( value ) );
        return this;
    }

    HeartGauge* HeartGauge::scriptDownAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( -value ) );
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
        return CallFunc::create( [ this, value ]
        {
            auto targetValue = clampf( now + value, 0, max );
            UserDefault::getInstance( )->setIntegerForKey( u8"親愛度", targetValue );
            auto rect = background->getTextureRect( );
            background->runAction( ActionFloat::create( 1.0F, now, targetValue, [ = ] ( float t )
            {
                background->setTextureRect( Rect( rect.origin.x, rect.origin.y, start + getWidth( t ), rect.size.height ) );
            } ) );
        } );
    }

    cocos2d::Sequence* HeartGauge::createInValueStopOutExitAction( int value )
    {
        auto size = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto targetSize = Size( 512, 196 ) * 0.75;
        auto slideSize = targetSize.height;
        auto pos = getPosition( ) + Vec2( 0, slideSize );
        setPosition( pos );
        auto movein = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 0, -slideSize ) ) );
        auto moveout = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 0, slideSize ) ) );

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
