# ifndef __BGManager__
# define __BGManager__

# include "cocos2d.h"

namespace User
{
    class BGManager : public cocos2d::Layer
    {
    public:
		BGManager() {}
		~BGManager() {}
		bool init();

		CREATE_FUNC(BGManager);
    private:

    };
}

# endif // __BGManager__
