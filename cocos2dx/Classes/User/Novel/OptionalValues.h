# ifndef __OptionalValues__
# define __OptionalValues__

# include "cocos2d.h"

namespace User
{
    class OptionalValues
    {
    public:
        static void setup( );
    public:
        static int stringSize;
        static float lineSpaceSize;
        static float fontSize;
        static float lineViewSize;
        static cocos2d::Vec2 stringViewSize;
        static cocos2d::Vec2 messageViewSize;
        static float readOutSpeed;
        static float maxReadOutSpeed;
        static std::string fontName;
        static cocos2d::Color4B fontColor;
        static cocos2d::Color4B fontShadowColor;
    };
}

# endif // __OptionalValues__
