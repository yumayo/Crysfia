#include "Utilitys.h"

namespace Lib
{
    float fitWidth( cocos2d::Node * node, float targetSize )
    {
        return targetSize / node->getContentSize( ).width;
    }

    float fitHeight( cocos2d::Node * node, float targetSize )
    {
        return targetSize / node->getContentSize( ).height;
    }

}