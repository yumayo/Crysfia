# ifndef __DiaryLabelData__
# define __DiaryLabelData__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace User
{
class DiaryLabelData
{
public:
    DiaryLabelData( std::string relativePath );
public:
    std::string title;
    std::vector<std::string> labels;
};
}

# endif // __DiaryLabelData__
