# ifndef __DiaryLabelList__
# define __DiaryLabelList__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace User
{
class DiaryLabelList : public cocos2d::ui::ListView
{
public:
    static DiaryLabelList* create( std::vector<std::string> const& labels );
    bool init( std::vector<std::string> const& labels );
};
}

# endif // __DiaryLabelList__
