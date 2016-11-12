# ifndef __SceneCreaning__
# define __SceneCreaning__

# include "cocos2d.h"
#include "../SceneBase.h"

namespace User
{
    class SceneCreaning : public SceneBase
    {
    public:
        SceneCreaning( );
        ~SceneCreaning( );

		cocos2d::Scene* create()override;
    
	private:
    
	};
}

# endif // __SceneCreaning__
