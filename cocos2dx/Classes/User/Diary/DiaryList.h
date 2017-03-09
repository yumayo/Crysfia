# ifndef __DiaryList__
# define __DiaryList__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace User
{
class DiaryList : public cocos2d::ui::ListView
{
public:
    static DiaryList* create( );
    bool init( );
};
}

# endif // __DiaryList__
