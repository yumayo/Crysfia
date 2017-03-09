# ifndef __DiaryWindow__
# define __DiaryWindow__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DiaryLabelData.h"

namespace User
{
class DiaryWindow : public cocos2d::ui::Layout
{
public:
    static DiaryWindow* create( DiaryLabelData const& data );
    bool init( DiaryLabelData const& data );
    static cocos2d::Node* _layer;
    void setOpen( bool value );
private:
    cocos2d::ui::Button* _button = nullptr;
};
}

# endif // __DiaryWindow__
