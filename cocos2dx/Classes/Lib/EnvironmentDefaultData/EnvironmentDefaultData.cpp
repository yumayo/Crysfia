#include "EnvironmentDefaultData.h"

USING_NS_CC;

namespace Lib
{
    EnvironmentDefaultData * EnvironmentDefaultData::mInstans = nullptr;
    EnvironmentDefaultData::EnvironmentDefaultData( )
    {
        designResolutionSize = cocos2d::Size( 720, 1280 );
        smallResolutionSize = cocos2d::Size( 270, 480 );
        mediumResolutionSize = smallResolutionSize * 2;
        largeResolutionSize = smallResolutionSize * 3;
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