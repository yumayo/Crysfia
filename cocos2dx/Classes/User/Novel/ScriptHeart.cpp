#include "ScriptHeart.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "INIWriter.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

Vec2 operator*( Vec2 const& left, Vec2 const& right )
{
    return Vec2( left.x * right.x, left.y * right.y );
}

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

        // ハートアイコン
        auto icon = Sprite::create( u8"res/texture/system/heart.icon.png" ); if ( !icon ) return this;
        // 親愛度のゲージ
        auto frame = Sprite::create( u8"res/texture/system/heart.frame.png" ); if ( !frame ) return this;


        // よって、レイアウトのサイズは、アイコンの横と、ゲージの横を足した値。
        // 縦はアイコンの方を使います。
        setContentSize( Size( icon->getContentSize( ).width + frame->getContentSize( ).width,
                              std::max( icon->getContentSize( ).height, frame->getContentSize( ).height ) ) );
        setAnchorPoint( Vec2( 0, 1 ) );

        // アイコンの設定
        {
            icon->setAnchorPoint( Vec2( 0, 0.5 ) );
            icon->setPosition( 0, getContentSize( ).height * 0.5 );
            addChild( icon );
        }

        // ゲージの設定
        {
            frame->setAnchorPoint( Vec2( 0, 0.5 ) );
            frame->setPosition( icon->getContentSize( ).width, getContentSize( ).height * 0.5 );
            addChild( frame );
        }

        // 画像のピクセル数を登録しておきます。
        {
            size = frame->getTexture( )->getContentSizeInPixels( );
        }

        // 現在の親愛度を登録。
        now = UserDefault::getInstance( )->getIntegerForKey( u8"親愛度" );

        // マスクを取る位置を決めます。
        // startはゲージの左端の大きさ。
        start = 5;
        // endはゲージの右端までの長さ。
        end = size.width - 5;

        // ここからマスクの処理を書きます。
        if ( auto clipping = ClippingNode::create( ) )
        {
            {
                // クリッピングノードはゲージの子供とします。
                frame->addChild( clipping );
                // ただしそのときに、原点を合わせるため以下の数値を代入しておきます。
                clipping->setPosition( frame->getAnchorPoint( ) * frame->getContentSize( ) );
            }

            // 実際に書き込むのは色のある部分です。
            clipping->setInverted( false );
            // 透明部分をマスクします。
            clipping->setAlphaThreshold( 0.0 );

            // マスク画像を用意します。
            if ( auto mask = Sprite::create( "res/texture/system/heart.mask.png" ) )
            {
                clipping->setStencil( mask );
                mask->setAnchorPoint( Vec2( 0, 0.5 ) );

            }

            // 塗りつぶすイメージを用意します。
            // ここでループ画像として使うので、サイズは2のべき乗固定です。
            if ( auto background = Sprite::create( u8"res/texture/system/favoritegauge.png",
                                                   Rect( 0, 0, ( start + getWidth( now ) ) * scale, size.height * scale ) ) )
            {
                this->background = background;
                clipping->addChild( background );
                background->setAnchorPoint( Vec2( 0, 0.5 ) );
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
        setScale( Lib::fitWidth( this, Director::getInstance( )->getVisibleSize( ).width / 2 ) );
        return this;
    }

    HeartGauge* HeartGauge::scriptDownAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( -value ) );
        setScale( Lib::fitWidth( this, Director::getInstance( )->getVisibleSize( ).width / 2 ) );
        return this;
    }

    HeartGauge * HeartGauge::up( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createValueAction( value ) );
        return this;
    }

    HeartGauge * HeartGauge::down( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createValueAction( -value ) );
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
        auto pixel = getContentSize( ) / scale;
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
