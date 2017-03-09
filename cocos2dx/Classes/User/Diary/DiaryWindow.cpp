#include "DiaryWindow.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"
#include "DiaryLabelLayout.h"

USING_NS_CC;

namespace User
{
cocos2d::Node* DiaryWindow::_layer = nullptr;
DiaryWindow * DiaryWindow::create( DiaryLabelData const& data )
{
    DiaryWindow *pRet = new( std::nothrow ) DiaryWindow( );
    if ( pRet && pRet->init( data ) )
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
bool DiaryWindow::init( DiaryLabelData const& data )
{
    if ( !ui::Layout::init( ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    auto p = ui::Button::create( "res/texture/system/board.png", "res/texture/system/board_on.png" );
    p->setScale( Lib::fitWidth( p, vs.width * 0.7 ) );
    setContentSize( p->getContentSize( ) * p->getScale( ) + Size( 0, 32 / 2 * scale ) );
    p->setAnchorPoint( Vec2( 0.5F, 0.5F ) );
    p->setPosition( getContentSize( ) * 0.5F );
    p->addTouchEventListener( [ this, data ] ( Ref*, ui::Widget::TouchEventType type )
    {
        if ( type == ui::Widget::TouchEventType::ENDED )
        {
            AudioManager::getInstance( )->playSe( "res/sound/SE/click.mp3" );
            _layer->addChild( DiaryLabelLayout::create( data ) );
        }
    } );
    addChild( p );
    _button = p;

    // 日記「ほげほげ」から ほげほげ の部分を取り出します。
    // それをボタンのタイトルとして配置します。
    auto title = data.title;
    title = title.substr( title.find( u8"「" ) + std::string( u8"「" ).size( ) );
    title = title.substr( 0, title.find( u8"」" ) );

    auto l = ui::Text::create( title, "res/fonts/F910MinchoW3.otf", 64 * scale );
    l->setPosition( getContentSize( ) * 0.5F );
    addChild( l );

    return true;
}
void DiaryWindow::setOpen( bool value )
{
    _button->setEnabled( value );
}
}
