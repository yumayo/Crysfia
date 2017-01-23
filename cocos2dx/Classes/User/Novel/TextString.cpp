#include "TextString.h"

#include "TextTypes.hpp"
#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    TextString::TextString( cocos2d::Layer* layer )
        : layer( layer )
    {

    }
    TextString::~TextString( )
    {
    }
    void TextString::actionStart( )
    {
        setActionStart( label->getStringLength( ) );
    }
    void TextString::actionAndCallfuncStart( std::function<void( )> const & actionCallfunc )
    {
         // 例外処理
         // 空行だった場合文字列自体がないためその次の行が存在していても、コールバック呼び出しができず表示できないため。
        if ( text == u8"" )
        {
            actionCallfunc( );
            return;
        }

        // 文字数(最後の文字を含まない)
        int stringIndex = label->getStringLength( ) - 1;

        // 最後の文字以外は通常の処理。
        setActionStart( stringIndex );

        // 一番最後の文字だけ特別処理
        // 次の文字列のアクションを最後の文字が表示された後に始めます。
        auto oneString = label->getLetter( stringIndex );
        if ( oneString )
        {
            oneString->runAction( Sequence::create( DelayTime::create( OptionalValues::readOutSpeed * stringIndex ),
                                                    FadeIn::create( OptionalValues::readOutSpeed ),
                                                    CallFunc::create( [ = ] { actionCallfunc( ); } ),
                                                    nullptr ) )->setTag( stringIndex ); // actionには何文字目かの情報を入れておきます。
        }
    }
    void TextString::actionStop( )
    {
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString )
            {
                oneString->stopActionByTag( i );
                oneString->setOpacity( 255 );
            }
        }
    }
    void TextString::layerPasting( )
    {
        layer->addChild( label );
    }
    void TextString::layerPeelOff( )
    {
        layer->removeChildByTag( (int)Tag::Novel );
    }
    void TextString::setLabelString( std::string const & text )
    {
        this->text = text;
        label = Label::createWithTTF( text, OptionalValues::fontName, OptionalValues::fontSize );
        label->enableShadow( OptionalValues::fontShadowColor, Size( 2, -2 ), 2 );
        label->setTextColor( OptionalValues::fontColor );
        label->setTag( (int)Tag::Novel );
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString ) oneString->setOpacity( 0 );
        }

        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto win_size = Director::getInstance( )->getWinSize( );
        auto contentWidth = label->getContentSize( ).width;
        if ( visibleWidth * ( 614.0F / 720 ) <= contentWidth )
        {
            label->setScaleX( ( visibleWidth * ( 614.0F / 720 ) ) / contentWidth );
        }
    }
    void TextString::setDrawPosition( cocos2d::Vec2 position )
    {
        float width;
        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto contentSize = label->getContentSize( );
        if ( visibleWidth * ( 614.0F / 720 ) <= contentSize.width ) width = visibleWidth * ( 614.0F / 720 )  * 0.5;
        else width = contentSize.width * 0.5;

        label->setPosition( position + Vec2( width, 0 ) );
    }
    void TextString::setActionStart( size_t stringLength )
    {
        for ( int i = 0; i < stringLength; i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString )
            {
                oneString->runAction( Sequence::create( DelayTime::create( OptionalValues::readOutSpeed * i ),
                                                        FadeIn::create( OptionalValues::readOutSpeed ),
                                                        nullptr ) )->setTag( i );
            }
        }
    }
}
