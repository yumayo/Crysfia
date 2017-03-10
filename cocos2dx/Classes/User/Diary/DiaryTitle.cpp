#include "DiaryTitle.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
bool DiaryTitle::init( )
{
    if ( !Sprite::initWithFile( "res/texture/diary/title.png" ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setScale( Lib::fitWidth( this, vs.width * 0.8 ) );

    setPosition( vo + Vec2( vs.width * 0.5, vs.height - vs.width * 0.2 ) );

    return true;
}
}
