# pragma once
# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "../../Lib/json.h"
# include "LayerCity.h"

namespace User
{
    // フェードイン
    // 半透明の黒色
    // タップしたら、フェードアウトして削除。
    class LayerNovelView : public cocos2d::LayerColor
    {
    public:
        static LayerNovelView* create( ScenarioPointData const& scenario, std::function<void()> const& saveCallFunc );
        bool init( ScenarioPointData const& scenario, std::function<void( )> const& saveCallFunc );
    private:
        std::function<void( )> saveCallFunc;
        bool isNext = false;
    };
}