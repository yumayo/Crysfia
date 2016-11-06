# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        void initBackground( );
        void initCountry( );
        void initListener( );
    private:
        bool isDebug = false;
        cocos2d::ui::Button* createDebugButton( );
    private:
        // 背景画像をウィンドウの縦にピッタリと合わせるサイズ
        float backgroundWindowHeightFitScale;
        cocos2d::Vec2 translate;
        cocos2d::Size targetSize;
        cocos2d::Sprite* background;
    };
}

# endif // __LayerIsland__
