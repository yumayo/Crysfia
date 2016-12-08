#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

#include "../SceneManager.h"

#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( std::string const & novelPath )
        : textLabels( this )
        , novelPath( novelPath )
        , readProceed( false )
        , systemRead( true )
        , systemStop( false )
    {
    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                //textData.makeData( novelPath );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�L�[�������ꂽ�獂���ǂݍ��݂��J�n����B
                readProceed.on( );
            }
        };
        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�������ꂽ�獂���ǂݍ��݂��~����B
                readProceed.off( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto multiTouchEvent = EventListenerTouchAllAtOnce::create( );
        multiTouchEvent->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                click( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( multiTouchEvent, this );

        //auto mouseEvent = EventListenerMouse::create( );
        //mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        //{
        //    if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
        //    {
        //        textUpdate( );
        //    }
        //};
        //this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );


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

        textChunkManager.readEndCallBack = [ this ]
        {
            // �e�L�X�g�f�[�^��\��t���āB
            textPasting( );
            // �V�X�e���ǂݍ��݂��~�B
            systemRead.off( );
        };
        textChunkManager.novelEndCallBack = [ this ]
        {
            SceneManager::createIslandMap( );
        };

        textChunkManager.make( novelPath );
    }
    void NovelLayer::update( float delta )
    {
        textChunkManager.updateDelay( delta );

        // �����ǂݍ��݂̃A�b�v�f�[�g
        // �L�[�{�[�h�̍�����CTRL�������Ă���Ԃ��������ǂݍ��݋@�\��ON�ɂȂ�܂��B
        readingProceedUpdate( );

        // �e�L�X�g�̓ǂݍ��݁B
        // delay��0�ł������A�e�L�X�g��ǂݍ��ݑ����܂��B
        readNextNovel( );
    }
    void NovelLayer::on( )
    {
        this->resume( );
        this->setVisible( true );
    }
    void NovelLayer::off( )
    {
        this->pause( );
        this->setVisible( false );
    }
    void NovelLayer::select( std::string const & name )
    {
        systemStop.off( );

        auto selectLayer = this->getLayer<SelectLayer>( );

        // �I�����̃��C���[���폜
        if ( auto ptr = dynamic_cast<Menu*>( selectLayer->getChildByName( u8"select" ) ) )
        {
            ptr->setEnabled( false );
            ptr->runAction( Sequence::create( FadeOut::create( 0.3 ), RemoveSelf::create( ), nullptr ) );
        }

        // ���ɓǂݍ��ރV�i���I�f�[�^���w��B
        textChunkManager.select( name );
    }
    void NovelLayer::textClear( )
    {
        textChunkManager.gotoNext( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // �e�L�X�g�f�[�^��ǂݍ��ݏI������烉�x���ɓ\��t����B
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChunkManager.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
    void NovelLayer::readingProceedUpdate( )
    {
        // �����ǂݍ��݂��\�Ȃ當����1�t���[����1��ǂݑ�����B
        if ( readProceed )
        {
            // �����ǂݍ��݂ł�delay�͖������܂��B
            textChunkManager.setDelayTime( 0.0F );
            click( );
        }
    }
    void NovelLayer::click( )
    {
        if ( textLabels.getIsReadOuted( ) )
        {
            makeLoadingFeatureOn( );
        }
        else
        {
            textActionStop( );
        }
    }
    //�@�e�L�X�g�̃A�j���[�V�������I����Ă���ꍇ
    void NovelLayer::makeLoadingFeatureOn( )
    {
        // �V�����e�L�X�g��ǂݍ���ŗǂ��ꍇ�B
        if ( !systemStop )
        {
            // �e�L�X�g�̒��g�������܂��B
            textClear( );
            // �ǂݍ��݂��J�n�̍��}���o���܂��B
            systemRead.on( );
        }
    }
    void NovelLayer::readNextNovel( )
    {
        if ( systemRead )
        {
            textChunkManager.textRead( );
        }
    }
    // �e�L�X�g�̃A�j���[�V�������I����Ă��Ȃ��ꍇ
    void NovelLayer::textActionStop( )
    {
        textChunkManager.setDelayTime( 0.0F );
        readNextNovel( );

        textLabels.actionStop( );
    }
}
