#ifndef __EnvironmentDefaultData__
#define __EnvironmentDefaultData__

# include "cocos2d.h"

namespace Lib
{
    class EnvironmentDefaultData
    {
    private:
        EnvironmentDefaultData( );
    public:
        ~EnvironmentDefaultData( );
        static EnvironmentDefaultData * getInstance( );
    private:
        static EnvironmentDefaultData * mInstans;
    public:
        cocos2d::Size designResolutionSize;
        cocos2d::Size smallResolutionSize;
        cocos2d::Size mediumResolutionSize;
        cocos2d::Size largeResolutionSize;
        std::string gameName;
    };
}

using Env = Lib::EnvironmentDefaultData;

#endif // __EnvironmentDefaultData__