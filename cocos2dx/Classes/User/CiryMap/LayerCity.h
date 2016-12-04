# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class Mark : public cocos2d::Sprite
    {
    protected:
        /**
         *  すでに読んだシナリオなのかどうか。
         *  @true   読んでいたら
         *  @false  未読なら
         */
        bool isChecked;
    };

    class MainMark : public Mark
    {
    public:
        static MainMark* createMark( );
        MainMark( ) { }
        ~MainMark( ) { }
    private:
        CREATE_FUNC( MainMark );
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& backgroundPath );
        ~LayerCity( );
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
    private:
        std::string backgroundPath;

        /**
         * 次の行動目的を表示するためのデータ。
         */
        std::map<std::string, cocos2d::Data> data;

        /**
         *  月
         */
        int month;

        /**
         *  日
         */
        int day;

        /**
         *  時刻
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
        Times times;



    };
}

# endif // __LayerCity__
