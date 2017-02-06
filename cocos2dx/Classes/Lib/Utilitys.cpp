#include "Utilitys.h"

USING_NS_CC;

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

    void next_day( )
    {
        // 次に、時間を一段階進めます。
                    // 朝→夕→夜
        int translate = -1;
        auto time = UserDefault::getInstance( )->getIntegerForKey( u8"時刻" ) + translate;
        if ( 3 <= ( time + 1 ) ) // 繰り上がったら
        {
            auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
            UserDefault::getInstance( )->setIntegerForKey( u8"日", day + 1 );
        }
        time = ( time + 1 ) % 3;
        UserDefault::getInstance( )->setIntegerForKey( u8"時刻", time - translate );
    }

}