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
         // ��O����
         // ��s�������ꍇ�����񎩑̂��Ȃ����߂��̎��̍s�����݂��Ă��Ă��A�R�[���o�b�N�Ăяo�����ł����\���ł��Ȃ����߁B
        if ( text == u8"" )
        {
            actionCallfunc( );
            return;
        }

        // ������(�Ō�̕������܂܂Ȃ�)
        int stringIndex = label->getStringLength( ) - 1;

        // �Ō�̕����ȊO�͒ʏ�̏����B
        setActionStart( stringIndex );

        // ��ԍŌ�̕����������ʏ���
        // ���̕�����̃A�N�V�������Ō�̕������\�����ꂽ��Ɏn�߂܂��B
        auto oneString = label->getLetter( stringIndex );
        if ( oneString )
        {
            oneString->runAction( Sequence::create( DelayTime::create( OptionalValues::readOutSpeed * stringIndex ),
                                                    FadeIn::create( OptionalValues::readOutSpeed ),
                                                    CallFunc::create( [ = ] { actionCallfunc( ); } ),
                                                    nullptr ) )->setTag( stringIndex ); // action�ɂ͉������ڂ��̏������Ă����܂��B
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
                oneString->setOpacity( 256 );
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
        label = Label::createWithTTF( text, u8"res/fonts/F910MinchoW3.otf", OptionalValues::fontSize );
        label->setTextColor( Color4B::WHITE );
        label->setTag( (int)Tag::Novel );
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString ) oneString->setOpacity( 0 );
        }

        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto contentWidth = label->getContentSize( ).width;
        if ( visibleWidth * 0.9 <= contentWidth )
        {
            label->setScaleX( ( visibleWidth * 0.9 ) / contentWidth );
        }
    }
    void TextString::setDrawPosition( cocos2d::Vec2 position )
    {
        float width;
        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto contentSize = label->getContentSize( );
        if ( visibleWidth * 0.9 <= contentSize.width ) width = visibleWidth * 0.9 * 0.5;
        else width = contentSize.width * 0.5;

        label->setPosition( position + Vec2( width, -contentSize.height ) );
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
