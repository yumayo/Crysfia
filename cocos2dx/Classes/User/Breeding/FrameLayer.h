# ifndef __FrameLayer__
# define __FrameLayer__

# include "cocos2d.h"

namespace User
{
    class FrameLayer : public cocos2d::Layer
    {
    public:
		CREATE_FUNC(FrameLayer);
		bool init();
    };
}

# endif // __FrameLayer__
