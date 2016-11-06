# ifndef __SceneNovel__
# define __SceneNovel__

# include "cocos2d.h"

# include "../SceneBase.h"

namespace User
{
    class SceneNovel : public SceneBase
    {
    public:
        SceneNovel( std::string const& novelPath );
    public:
        cocos2d::Scene* create( ) override;
    private:
        std::string novelPath;
    };
}

# endif // __SceneNovel__
