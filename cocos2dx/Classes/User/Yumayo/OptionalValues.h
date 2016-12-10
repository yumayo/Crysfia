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
        static cocos2d::Vec2 stringViewSize;
        static float readOutSpeed;
    };
}

# endif // __OptionalValues__
