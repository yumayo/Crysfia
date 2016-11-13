#include "ScriptHeart.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "INIWriter.h"

USING_NS_CC;

namespace User
{
    ScriptHeart::ScriptHeart( cocos2d::Layer * layer, std::string const & filePath )
        : ScriptBase( layer )
        , filePath( filePath )
    {
        REGIST_FUNC( ScriptHeart, up );
        REGIST_FUNC( ScriptHeart, down );

        auto file = FileUtils::getInstance( );
        auto path = file->getWritablePath( ) + filePath;
        if ( file->isFileExist( path ) )
        {
            reader.read( path );
        }
        else
        {
            reader.read( u8"res/data/" + filePath );
        }
    }
    ScriptHeart::~ScriptHeart( )
    {
        INIWriter::write( filePath, reader );
    }
    void ScriptHeart::favorabilityRating( int value )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto contentScale = Director::getInstance( )->getContentScaleFactor( );

        auto slideSize = visibleSize.height * 0.1;

        auto layout = ui::Layout::create( );
        layer->addChild( layout );
        layout->setTag( (int)Tag::Heart );
        layout->setPosition( origin + Vec2( 0, visibleSize.height + slideSize ) );
        auto movein = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 0, -slideSize ) ) );
        auto moveout = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( 0, slideSize ) ) );

        auto targetSize = Size( 512, 196 ) / 2;
        auto left = 81.0F / 2;
        auto right = targetSize.width - left;

        auto clipping = ClippingNode::create( );
        if ( !clipping ) return;
        layout->addChild( clipping );
        {
            auto mask = Sprite::create( "res/texture/system/frame.mask.png" );
            if ( !mask ) return;
            {
                auto size = mask->getContentSize( );
                mask->setAnchorPoint( Vec2( 0, 1 ) );
                mask->setScale( targetSize.width / size.width, targetSize.height / size.height );
            }
            clipping->setTag( (int)Tag::Heart );
            clipping->setStencil( mask );
            clipping->setInverted( false );
            clipping->setAlphaThreshold( 0.0 );

            auto max = 100;
            auto& data = reader[u8"ÉNÉçÉG"][u8"now"];
            int now = 0;
            try
            {
                now = StringUtil::string_value<int>( data );
            }
            catch ( ... )
            {
                throw( "ïœêîÇ™êîéöÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒÅB" );
            }
            auto targetValue = clampf( now + value, 0, max );
            data = StringUtil::value_string<int>( targetValue );

            auto getWidth = [ = ] ( float now ) { return ( right - left ) * ( now / max ); };
            auto background = Sprite::create( u8"res/texture/system/favoritegauge.jpg", Rect( 0, 0, left + getWidth( now ), targetSize.height ) );
            if ( !background ) return;
            {
                auto up = ActionFloat::create( 1.0F, now, targetValue, [ = ] ( float t )
                {
                    auto rect = background->getTextureRect( );
                    background->setTextureRect( Rect( rect.origin.x, rect.origin.y, left + getWidth( t ), rect.size.height ) );
                } );
                auto stop = DelayTime::create( 1.0 );
                auto exit = RemoveSelf::create( );
                layout->runAction( Sequence::create( movein, up, stop, moveout, exit, nullptr ) );
                background->setAnchorPoint( Vec2( 0, 1 ) );
                background->getTexture( )->setTexParameters( { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT } );
                clipping->addChild( background );
            }
        }

        auto frame = Sprite::create( u8"res/texture/system/frame.png" );
        if ( !frame ) return;
        layout->addChild( frame );
        {
            auto size = frame->getContentSize( );
            frame->setAnchorPoint( Vec2( 0, 1 ) );
            frame->setScale( targetSize.width / size.width, targetSize.height / size.height );
        }
    }
    SCRIPT( ScriptHeart::up )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto value = StringUtil::string_value<int>( args[0] );
            if ( value < 1 ) return;
            favorabilityRating( value );
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
            auto value = StringUtil::string_value<int>( args[0] );
            if ( value < 1 ) return;
            favorabilityRating( -value );
        }
        break;
        default:
            break;
        }
    }
}
