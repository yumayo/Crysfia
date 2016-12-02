# ifndef __FGManager__
# define __FGManager__

# include "cocos2d.h"

namespace User
{
    class FGManager : public cocos2d::Layer
    {
    public:
		CREATE_FUNC(FGManager);
        FGManager( );
        ~FGManager( );

		void fadeInForeground();
		void fadeOutForeground();
		
    private:
		cocos2d::Size winSize;
		bool init();
    };
}

# endif // __FGManager__
