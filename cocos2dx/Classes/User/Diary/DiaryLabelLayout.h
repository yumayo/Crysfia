# ifndef __DiaryLabelLayout__
# define __DiaryLabelLayout__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DiaryLabelData.h"

namespace User
{
class DiaryLabelLayout : public cocos2d::ui::Layout
{
public:
    static DiaryLabelLayout* create( DiaryLabelData const& data );
    bool init( DiaryLabelData const& data );
};
}

# endif // __DiaryLabelLayout__
