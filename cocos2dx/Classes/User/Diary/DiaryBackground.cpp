#include "DiaryBackground.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
bool DiaryBackground::init( )
{
    if ( !Sprite::initWithFile( "res/texture/diary/background.png" ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setAnchorPoint( { 0, 0 } );
    setScale( Lib::fitWidth( this, vs.width ) );

    return true;
}
}
