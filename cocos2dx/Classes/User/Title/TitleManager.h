# ifndef __TitleManager__
# define __TitleManager__

#include "../LayerBase.h"
#include "Lib/AudioManager.h"

namespace User
{
    class TitleManager : public LayerBase
    {
    public:
        TitleManager( );
        ~TitleManager( );
		CREATE_FUNC(TitleManager);
    private:

		bool init();
		void createTitleWindow();
		void createTapUI();
		void createFadeSprite();
		void update(float dt);
		
		bool isTap;
		bool isGameStarted;
		float vol;

		AudioManager* audioManager;

		cocos2d::Sprite* fadeSprite;
		cocos2d::Label*  uiLabel;
		cocos2d::Action* normalAction();
		cocos2d::Action* afterAction();
		cocos2d::Action* fadeAction(float _fadeTime, float _delayTime);
    };
}

# endif // __TitleManager__