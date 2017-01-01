# pragma once
# include "cocos2d.h"
# include "ui/CocosGUI.h"

namespace User
{
    // フェードイン
    // 半透明の黒色
    // タップしたら、フェードアウトして削除。
    class LayerNovelView : public cocos2d::LayerColor
    {
    public:
        static LayerNovelView* create( std::string const& title );
        bool init( std::string const& title );
    };
}