# ifndef __DiaryBackButton__
# define __DiaryBackButton__

#include "ui/CocosGUI.h"

namespace User
{
class DiaryBackButton : public cocos2d::ui::Button
{
public:
    static DiaryBackButton* create( );
    bool init( );
};
}

# endif // __DiaryBackButton__
