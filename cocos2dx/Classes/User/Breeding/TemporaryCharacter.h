# ifndef __TemporaryCharacter__
# define __TemporaryCharacter__

# include "cocos2d.h"
#include "../LayerBase.h"
//キャラクター仮置き用レイヤー
namespace User
{
    class TemporaryCharacter : public LayerBase
    {
    public:

		CREATE_FUNC(TemporaryCharacter);
        TemporaryCharacter( );
        ~TemporaryCharacter( );

    private:

		bool init();

		cocos2d::Size winSize;
		cocos2d::Sprite* character;
		cocos2d::Sprite* bottle;

    };
}

# endif // __TemporaryCharacter__
