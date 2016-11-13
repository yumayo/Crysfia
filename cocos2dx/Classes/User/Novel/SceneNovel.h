# ifndef __SceneNovel__
# define __SceneNovel__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneNovel : public SceneBase
    {
    public:
        static cocos2d::Scene* create( std::string const& novelPath );
    };
}

# endif // __SceneNovel__
