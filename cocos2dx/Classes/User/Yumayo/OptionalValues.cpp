#include "OptionalValues.h"

#include "TextTypes.hpp"

USING_NS_CC;

namespace User
{
    int OptionalValues::stringSize;
    float OptionalValues::lineSpaceSize;
    float OptionalValues::fontSize;
    cocos2d::Vec2 OptionalValues::stringViewSize;
    float OptionalValues::readOutSpeed;

    void OptionalValues::setup( )
    {
        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto stringViewWidth = visibleWidth * 0.9;

        readOutSpeed = 0.1F;
        stringSize = 20;
        fontSize = stringViewWidth / stringSize;
        lineSpaceSize = fontSize * 0.7;
        stringViewSize = Vec2( stringViewWidth,
            ( fontSize + lineSpaceSize ) * lineSize );
    }
}
