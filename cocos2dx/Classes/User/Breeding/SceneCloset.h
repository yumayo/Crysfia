# ifndef __SceneCloset__
# define __SceneCloset__
# include "cocos2d.h"
#include "../SceneBase.h"

namespace User
{
    class SceneCloset : public SceneBase
    {
    public:
        SceneCloset( );
        ~SceneCloset( );
    
		cocos2d::Scene* create()override;
	
	private:
    
	};
}

# endif // __SceneCloset__
