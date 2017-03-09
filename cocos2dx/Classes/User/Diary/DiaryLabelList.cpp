#include "DiaryLabelList.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"
#include "DiaryLabel.h"

USING_NS_CC;

namespace User
{
DiaryLabelList * DiaryLabelList::create( std::vector<std::string> const& labels )
{
    DiaryLabelList *pRet = new( std::nothrow ) DiaryLabelList( );
    if ( pRet && pRet->init( labels ) )
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
bool DiaryLabelList::init( std::vector<std::string> const& labels )
{
    if ( !ui::ListView::init( ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setContentSize( Size( vs.width * 0.8, vs.height - vs.width * 0.6 ) );
    setAnchorPoint( Vec2( 0.5, 0.5 ) );
    setPosition( vo + vs * 0.5F );

    setGravity( ui::ListView::Gravity::CENTER_HORIZONTAL );

    for ( auto& line : labels )
    {
        addChild( DiaryLabel::create( line ) );
    }

    return true;
}
}
