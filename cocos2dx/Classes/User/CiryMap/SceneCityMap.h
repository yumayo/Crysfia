# ifndef __SceneCityMap__
# define __SceneCityMap__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneCityMap : public SceneBase
    {
    public:
        static cocos2d::Scene* create( std::string const& backgroundPath );
    };
}

# endif // __SceneCityMap__
