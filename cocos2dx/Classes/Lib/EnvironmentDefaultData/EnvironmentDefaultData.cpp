#include "EnvironmentDefaultData.h"

USING_NS_CC;

namespace Lib
{
    EnvironmentDefaultData * EnvironmentDefaultData::mInstans = nullptr;
    EnvironmentDefaultData::EnvironmentDefaultData( )
    {
        designResolutionSize = cocos2d::Size( 1280, 720 );
        smallResolutionSize = cocos2d::Size( 480, 320 );
        mediumResolutionSize = cocos2d::Size( 1024, 768 );
        largeResolutionSize = cocos2d::Size( 2048, 1536 );
        gameName = std::string( "Crysfia" );
    }
    EnvironmentDefaultData::~EnvironmentDefaultData( )
    {
        CC_SAFE_DELETE( mInstans );
    }
    EnvironmentDefaultData * EnvironmentDefaultData::getInstance( )
    {
        if ( !mInstans ) mInstans = new EnvironmentDefaultData;

        return mInstans;
    }
}