#include "OptionalValues.h"

#include "TextTypes.hpp"

USING_NS_CC;

namespace User
{
    int OptionalValues::stringSize;
    float OptionalValues::lineSpaceSize;
    float OptionalValues::fontSize;
    float OptionalValues::lineViewSize;
    cocos2d::Vec2 OptionalValues::stringViewSize;
    cocos2d::Vec2 OptionalValues::messageViewSize;
    float OptionalValues::readOutSpeed;
    std::string OptionalValues::fontName;

    void OptionalValues::setup( )
    {
        auto visibleWidth = Director::getInstance( )->getVisibleSize( ).width;
        auto stringViewWidth = visibleWidth * 0.9;

        readOutSpeed = 0.1F;
        stringSize = 20;
        fontSize = stringViewWidth / stringSize;
        lineSpaceSize = fontSize * 0.7;
        lineViewSize = fontSize + lineSpaceSize;
        stringViewSize = Vec2( stringViewWidth, lineViewSize * lineSize );
        messageViewSize = Vec2( stringViewSize.x, stringViewSize.y + lineViewSize );
        fontName = u8"res/fonts/F910MinchoW3.otf";
    }
}
