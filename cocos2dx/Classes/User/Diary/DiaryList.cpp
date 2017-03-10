#include "DiaryList.h"
#include "../SceneManager.h"
#include "Lib/AudioManager.h"
#include "Lib/Utilitys.h"
#include "DiaryWindow.h"
#include "Lib/json.h"
#include "../System/DataSettings.h"
#include "DiaryLabelData.h"

USING_NS_CC;

namespace User
{
DiaryList * DiaryList::create( )
{
    DiaryList *pRet = new( std::nothrow ) DiaryList( );
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
bool DiaryList::init( )
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

    Json::Value diaryRoot;
    Json::Reader diaryReader;
    if ( !diaryReader.parse( FileUtils::getInstance( )->getStringFromFile( "res/diary/open.json" ), diaryRoot ) ) return false;

    Json::Value saveDataRoot;
    Json::Reader saveDataReader;
    if ( !saveDataReader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( "autosave.json", "res/data/" ) ), saveDataRoot ) ) return false;

    // 日記データを読み込む。
    struct DiaryData
    {
        std::string path;
        std::string scenaioName;
    };
    // データから日記の名前と、開放されるシナリオ名を保存します。
    std::vector<DiaryData> diarys;
    for ( auto& name : diaryRoot.getMemberNames( ) )
    {
        diarys.push_back( { name, diaryRoot[name][u8"visit"].asString( ) } );
    }

    auto find = [ &saveDataRoot ] ( std::string scenarioName ) -> bool
    {
        std::vector<std::string> islandNames = { u8"旅立ちの島", u8"ラシャス島", u8"ヒャルキシ島", u8"アイクラ島" };
        std::vector<std::string> tags = { u8"point.main", u8"point.sub", u8"point.force" };

        for ( auto& islandName : islandNames )
        {
            for ( auto& tag : tags )
            {
                auto& islandData = saveDataRoot[islandName][tag];
                for ( auto& point : islandData )
                {
                    if ( point[u8"scenario"] == scenarioName )
                    {
                        return point[u8"visit"].asBool( );
                    }
                }
            }
        }
        return false;
    };


    for ( auto& diary : diarys )
    {
        DiaryLabelData data( diary.path );
        auto window = DiaryWindow::create( data );
        window->setOpen( find( diary.scenaioName ) );
        addChild( window );
    }

    return true;
}
}
