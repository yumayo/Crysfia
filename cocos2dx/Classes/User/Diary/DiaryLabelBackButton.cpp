#include "DiaryLabelBackButton.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
DiaryLabelBackButton* DiaryLabelBackButton::create( cocos2d::Node * destroyNode )
{
    DiaryLabelBackButton *pRet = new( std::nothrow ) DiaryLabelBackButton( );
    if ( pRet && pRet->init( destroyNode ) )
    {
        pRet->autorelease( );
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
bool DiaryLabelBackButton::init( cocos2d::Node * destroyNode )
{
    if ( !ui::Button::init( "res/texture/diary/exit.png", "res/texture/diary/exit_select.png" ) ) return false;

    if ( !destroyNode ) return false;
    _destroyNode = destroyNode;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setScale( Lib::fitWidth( this, 128 * scale ) );
    setPosition( vo + Vec2 { vs.width * 0.1F, vs.width * 0.1F } );
    setAnchorPoint( { 0, 0 } );

    addTouchEventListener( [ this ] ( Ref*, ui::Widget::TouchEventType type )
    {
        if ( type == ui::Widget::TouchEventType::ENDED )
        {
            AudioManager::getInstance( )->playSe( "res/sound/SE/click.mp3" );
            _destroyNode->removeFromParent( );
        }
    } );

    return true;
}
}
