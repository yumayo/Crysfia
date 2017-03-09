#include "DiaryBackButton.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
DiaryBackButton* DiaryBackButton::create( )
{
    DiaryBackButton *pRet = new( std::nothrow ) DiaryBackButton( );
    if ( pRet && pRet->init( ) )
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
bool DiaryBackButton::init( )
{
    if ( !ui::Button::init( "res/texture/diary/exit.png", "res/texture/diary/exit_select.png" ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setScale( Lib::fitWidth( this, 128 * scale ) );
    setPosition( vo + Vec2{ vs.width * 0.1F, vs.width * 0.1F } );
    setAnchorPoint( { 0, 0 } );

    addTouchEventListener( [ this ] ( Ref*, ui::Widget::TouchEventType type )
    {
        if ( type == ui::Widget::TouchEventType::ENDED )
        {
            AudioManager::getInstance( )->playSe( "res/sound/SE/click.mp3" );
            SceneManager::createBreeding( );
        }
    } );

    return true;
}
}
