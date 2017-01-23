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
    float OptionalValues::maxReadOutSpeed;
    std::string OptionalValues::fontName;
    cocos2d::Color4B OptionalValues::fontColor;
    cocos2d::Color4B OptionalValues::fontShadowColor;

    void OptionalValues::setup( )
    {
        auto scale = 614.0F / 720;

        auto vs = Director::getInstance( )->getVisibleSize( );

        auto stringViewWidth = vs.width * scale;

        auto user = UserDefault::getInstance( );

        maxReadOutSpeed = 0.2;
        readOutSpeed = maxReadOutSpeed - user->getFloatForKey( u8"novel.speed" );
        stringSize = 20;
        fontSize = stringViewWidth / stringSize;
        lineSpaceSize = fontSize * 0.7;
        lineViewSize = fontSize + lineSpaceSize;
        stringViewSize = Vec2( stringViewWidth, lineViewSize * lineSize );
        messageViewSize = Vec2( stringViewSize.x, stringViewSize.y + lineViewSize );
        fontName = u8"res/fonts/F910MinchoW3.otf";
        fontColor = Color4B( 245, 245, 245, 255 );
        fontShadowColor = Color4B( 39, 39, 39, 255 );
    }
}
