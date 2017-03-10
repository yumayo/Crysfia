# ifndef __DiaryLabel__
# define __DiaryLabel__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace User
{
class DiaryLabel : public cocos2d::ui::Layout
{
public:
    static DiaryLabel* create( std::string title );
    bool init( std::string title );
};
}

# endif // __DiaryLabel__
