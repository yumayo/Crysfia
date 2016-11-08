#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( )
        : textLabels( this )
    {

    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                textData.makeData( "scenario1.txt" );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�L�[�������ꂽ�獂���ǂݍ��݂��J�n����B
                switchIsReadingProceed( );
            }
        };

        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL���b���ꂽ�獂���ǂݍ��݂��~����B
                switchIsReadingProceed( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto mouseEvent = EventListenerMouse::create( );
        mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        {
            if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
            {
                textUpdate( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

        return true;
    }
    void NovelLayer::setup( )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( origin.x, origin.y, visibleSize.width, OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        square->setPosition( rect.origin + rect.size / 2 );
        this->addChild( square );

        textData.makeData( "scenario1.txt" );
        textRead( );
    }
    void NovelLayer::update( float delta )
    {
        delayTime = std::max( delayTime - delta, 0.0 );

        // �����ǂݍ��݂̃A�b�v�f�[�g
        // �L�[�{�[�h�̍�����CTRL�������Ă���Ԃ��������ǂݍ��݋@�\��ON�ɂȂ�܂��B
        readingProceedUpdate( );

        // �e�L�X�g�̓ǂݍ��݁B
        // delay��0�ł������A�e�L�X�g��ǂݍ��ݑ����܂��B
        if ( isSystemRead ) textRead( );
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );

        // �I�����̃��C���[���폜
        selectLayer->removeAllChildren( );

        // ���ɓǂݍ��ރV�i���I�f�[�^���w��B
        textData.setNextChild( name );

        switchIsStopping( );
    }
    void NovelLayer::textRead( )
    {
        while ( delayTime == 0.0 )
        {
            // �e�L�X�g��ǂݎn�߂܂��B
            textPartyRead( );

            // �ǂݍ��ݏI���Ȃ�
            if ( textChank.isReadFinished( ) )
            {
                // �e�L�X�g�f�[�^��\��t���āB
                textPasting( );
                // �V�X�e���ǂݍ��݂��~�B
                switchIsSystemRead( );

                break;
            }
        }
    }
    void NovelLayer::textPartyRead( )
    {
        if ( !textChank.isReadFinished( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
        }
    }
    void NovelLayer::textClear( )
    {
        textChank.clear( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // �e�L�X�g�f�[�^��ǂݍ��ݏI������烉�x���ɓ\��t����B
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChank.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
    void NovelLayer::readingProceedUpdate( )
    {
        // �����ǂݍ��݂��\�Ȃ當����1�t���[����1��ǂݑ�����B
        if ( isReadingProceed )
        {
            // �����ǂݍ��݂ł�delay�͖������܂��B
            delayTime = 0.0F;
            textUpdate( );
        }
    }
    void NovelLayer::textUpdate( )
    {
        if ( textLabels.getIsReadOuted( ) )
        {
            textNextRead( );
        }
        else
        {
            textActionStop( );
        }
    }
    //�@�e�L�X�g�̃A�j���[�V�������I����Ă���ꍇ
    void NovelLayer::textNextRead( )
    {
        // �V�����e�L�X�g��ǂݍ���ŗǂ��ꍇ�B
        if ( !isStopping )
        {
            // �e�L�X�g�̒��g�������܂��B
            textClear( );
            // �ǂݍ��݂��J�n���܂��B
            switchIsSystemRead( );
        }
    }
    // �e�L�X�g�̃A�j���[�V�������I����Ă��Ȃ��ꍇ
    void NovelLayer::textActionStop( )
    {
        if ( isSystemRead )
        {
            textRead( );
        }

        textLabels.actionStop( );
    }
}
