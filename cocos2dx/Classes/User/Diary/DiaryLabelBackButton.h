# ifndef __DiaryLabelBackButton__
# define __DiaryLabelBackButton__

#include "ui/CocosGUI.h"

namespace User
{
class DiaryLabelBackButton : public cocos2d::ui::Button
{
public:
    static DiaryLabelBackButton* create( cocos2d::Node* destroyNode );
    bool init( cocos2d::Node * destroyNode );
private:
    cocos2d::Node* _destroyNode = nullptr;
};
}

# endif // __DiaryLabelBackButton__
