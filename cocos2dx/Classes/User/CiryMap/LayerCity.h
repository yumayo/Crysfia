# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct ScenarioPointData
    {
        /**
         *  データの初期化を行います。
         *  構造に必要なデータを一つ一つ詰めます。
         */
        void initData( bool isChecked, cocos2d::Vec2 const& position, std::string const& scenario )
        {
            this->isChecked = isChecked;
            this->position = position;
            this->scenario = scenario;
        }

        /**
         *  データの初期化を行います。
         *  コピーを取ってそのまま代入します。
         */
        void initData( ScenarioPointData const& scenario ) { *this = scenario; }

        /**
         *  すでに読んだシナリオなのかどうか。
         *  @true   読んでいたら
         *  @false  未読なら
         */
        bool isChecked;

        /**
         *  マップ画像中の表示位置。
         */
        cocos2d::Vec2 position;

        /**
         *  読み込むシナリオファイルのパス。
         */
        std::string scenario;
    };

    class Mark : protected ScenarioPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class MainMark : public Mark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class SubMark : public Mark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class Calendar : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( Calendar );
        Calendar* make( int day );
    private:
        /**
         *  カレンダーに表示する日にち。
         */
        int day;
    };

    class CityMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( CityMap );
        CityMap* make( std::string const& backgroundfile );
        void allChildCheckRemoved( );
    private:
        /**
         *  今の時間。
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
        Times times;

        /**
         *  画像をウィンドウの縦に収めるためのスケールです。
         *  このスケールを掛けると画像が縦画面にピッタリ収まります。
         */
        float backgroundWindowHeightFitScale;

        /**
         *  マップを横にスライドするときに使います。
         */
        cocos2d::Vec2 translate;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& backgroundPath );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        cocos2d::ui::Button* createBackButton( );
    private:
        std::string backgroundPath;

        /**
         * 次の行動目的を表示するためのデータ。
         */
        std::map<std::string, cocos2d::Data> data;
    };
}

# endif // __LayerCity__
