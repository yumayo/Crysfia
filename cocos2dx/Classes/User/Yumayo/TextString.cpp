#include "TextString.h"

#include "TextTypes.hpp"

USING_NS_CC;

namespace User
{
    float TextString::readOutSpeed = 0.1F;

    TextString::TextString( )
    {
        
    }
    TextString::~TextString( )
    {
    }
    void TextString::actionStart( )
    {
        setActionStart( label->getStringLength( ) );
    }
    void TextString::actionAndCallfuncStart( std::function<void( )> const & $actionCallfunc )
    {
        // コールバック関数を登録。
        actionCallfunc = $actionCallfunc;

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
            oneString->runAction( Sequence::create( DelayTime::create( readOutSpeed * stringIndex ),
                                                    Show::create( ),
                                                    DelayTime::create( readOutSpeed ),
                                                    CallFunc::create( [ this ] { actionCallfunc( ); } ),
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
                oneString->setVisible( true );
            }
        }
    }
    void TextString::layerPasting( cocos2d::Layer * layer )
    {
        layer->addChild( label );
    }
    void TextString::layerPeelOff( cocos2d::Layer * layer )
    {
        layer->removeChildByTag( (int)Tag::Novel );
    }
    void TextString::setReadOutSpeed( float $readOutSpeed )
    {
        readOutSpeed = $readOutSpeed;
    }
    void TextString::setLabelString( std::string const & text )
    {
        this->text = text;
        label = Label::createWithTTF( text, u8"fonts/F910MinchoW3.otf", 36.0F );
        label->setTextColor( Color4B::WHITE );
        label->setTag( (int)Tag::Novel );
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString ) oneString->setVisible( false );
        }
    }
    void TextString::setDrawPosition( cocos2d::Vec2 position )
    {
        auto size = label->getContentSize( );

        label->setPosition( position + Vec2( size.width / 2, 0 ) );
    }
    void TextString::setActionStart( size_t $stringLength )
    {
        for ( int i = 0; i < $stringLength; i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString )
            {
                oneString->runAction( Sequence::create( DelayTime::create( readOutSpeed * i ),
                                                        Show::create( ),
                                                        nullptr ) )->setTag( i );
            }
        }
    }
}
