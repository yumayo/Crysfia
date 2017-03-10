# ifndef __DiaryLabelTitle__
# define __DiaryLabelTitle__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace User
{
class DiaryLabelTitle : public cocos2d::ui::Layout
{
public:
    static DiaryLabelTitle* create( std::string title );
    bool init( std::string title );
};
}

# endif // __DiaryLabelTitle__
