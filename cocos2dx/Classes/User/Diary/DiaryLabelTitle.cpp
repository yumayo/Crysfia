#include "DiaryLabelTitle.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
DiaryLabelTitle * DiaryLabelTitle::create( std::string title )
{
    DiaryLabelTitle *pRet = new( std::nothrow ) DiaryLabelTitle( );
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
bool DiaryLabelTitle::init( std::string title )
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

    auto l = ui::Text::create( title, "res/fonts/F910MinchoW3.otf", 80 * scale );
    l->setTextColor( Color4B( 0, 0, 0, 255 ) );
    l->setPosition( Vec2( getContentSize( ).width * 0.5F, getContentSize( ).height * 0.75F ) );
    addChild( l );

    setAnchorPoint( Vec2( 0.5, 0.5 ) );
    setPosition( vo + Vec2( vs.width * 0.5F, vs.height - vs.width * 0.2 ) );

    return true;
}
}
