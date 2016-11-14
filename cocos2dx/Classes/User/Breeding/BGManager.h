# ifndef __BGManager__
# define __BGManager__
# include "cocos2d.h"
#include "VariousStatus.h"

namespace User
{
	class BGManager : public cocos2d::Layer
	{
	public:
		BGManager();
		~BGManager();
		bool init();

		void changeBackGround(int targetBG, int changeBG);

		CREATE_FUNC(BGManager);
	private:

		int homeBgm;
		std::vector<cocos2d::Sprite*> backgrounds;

	};
}

# endif // __BGManager__
