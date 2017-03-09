#include "DiaryLabel.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
DiaryLabel * DiaryLabel::create( std::string title )
{
    DiaryLabel *pRet = new( std::nothrow ) DiaryLabel( );
    if ( pRet && pRet->init( title ) )
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
bool DiaryLabel::init( std::string title )
{
    if ( !ui::Layout::init( ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    auto p = ui::ImageView::create( "res/texture/diary/line.png" );
    p->setScale( Lib::fitWidth( p, vs.width * 0.9 ) );
    setContentSize( p->getContentSize( ) * p->getScale( ) + Size( 0, 32 / 2 * scale ) );
    p->setAnchorPoint( Vec2( 0.5F, 0.5F ) );
    p->setPosition( getContentSize( ) * 0.5F );
    addChild( p );

    auto l = ui::Text::create( title, "res/fonts/F910MinchoW3.otf", 36 * scale );
    l->setTextColor( Color4B( 0, 0, 0, 255 ) );
    l->setPosition( getContentSize( ) * 0.5F );
    addChild( l );

    return true;
}
}
