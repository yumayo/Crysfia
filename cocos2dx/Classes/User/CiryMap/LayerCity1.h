# ifndef __LayerCity1__
# define __LayerCity1__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class LayerCity1 : public LayerBase
    {
    public:
        CREATE_FUNC( LayerCity1 );
        LayerCity1( );
        ~LayerCity1( );
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

# endif // __LayerCity1__
