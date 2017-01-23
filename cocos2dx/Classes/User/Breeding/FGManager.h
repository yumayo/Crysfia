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

		void fading(float _totalTime);

    private:

		cocos2d::Size winSize;
		bool init();

		cocos2d::Sprite* mask;
		
		bool isFadeIn;
		bool isFadeOut;
    };
}

# endif // __FGManager__
