#include "DiaryLabelLayout.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"
#include "DiaryLabelTitle.h"
#include "DiaryLabelList.h"
#include "DiaryBackground.h"
#include "DiaryLabelBackButton.h"

USING_NS_CC;

namespace User
{
DiaryLabelLayout * DiaryLabelLayout::create( DiaryLabelData const& data )
{
    DiaryLabelLayout *pRet = new( std::nothrow ) DiaryLabelLayout( );
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
bool DiaryLabelLayout::init( DiaryLabelData const& data )
{
    if ( !ui::Layout::init( ) ) return false;

    auto vo = Director::getInstance( )->getVisibleOrigin( );
    auto vs = Director::getInstance( )->getVisibleSize( );
    auto scale = Director::getInstance( )->getContentScaleFactor( );
    auto _scale = 1.0F / scale;

    setContentSize( vs );
    setAnchorPoint( Vec2( 0.5, 0.5 ) );
    setPosition( vo + vs * 0.5F );

    addChild( DiaryBackground::create( ) );
    addChild( DiaryLabelBackButton::create( this ) );
    addChild( DiaryLabelTitle::create( data.title ) );
    addChild( DiaryLabelList::create( data.labels ) );

    return true;
}
}
