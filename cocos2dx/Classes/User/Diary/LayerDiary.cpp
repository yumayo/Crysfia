#include "LayerDiary.h"
#include "DiaryBackButton.h"
#include "DiaryBackground.h"
#include "DiaryTitle.h"
#include "DiaryList.h"
#include "DiaryLabelLayout.h"
#include "DiaryWindow.h"

USING_NS_CC;

namespace User
{
bool LayerDiary::init( )
{
    if ( !Layer::init( ) ) return false;

    addChild( DiaryBackground::create( ) );
    addChild( DiaryTitle::create( ) );
    addChild( DiaryBackButton::create( ) );
    addChild( DiaryList::create( ) );

    DiaryWindow::_layer = this;

    return true;
}
}
