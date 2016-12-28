# ifndef __BGManager__
# define __BGManager__
# include "cocos2d.h"
#include "VariousStatus.h"

namespace User
{
	class BGManager : public cocos2d::Layer
	{
	public:
		
		CREATE_FUNC(BGManager);
		BGManager();
		~BGManager();
		bool init();

		void changeBackGround(int targetBG, int changeBG);

	private:

		int homeBgm;
		cocos2d::Size winSize;
		std::vector<cocos2d::Sprite*> backgrounds;

	};
}

# endif // __BGManager__
