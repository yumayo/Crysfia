# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

#include "../../Lib/json.h"

namespace User
{
    struct ScenarioPointData
    {
        /**
         *  データの初期化を行います。
         *  構造に必要なデータを一つ一つ詰めます。
         */
        void initData( bool visit, cocos2d::Vec2 const& position, std::string const& scenario )
        {
            this->visit = visit;
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
        bool visit;

        /**
         *  マップ画像中の表示位置。
         */
        cocos2d::Vec2 position;

        /**
         *  読み込むシナリオファイルのパス。
         */
        std::string scenario;

        /**
         *  このノベルのタイトル。
         */
        std::string title;
    };

    class LayerCityMark : protected ScenarioPointData, public cocos2d::ui::Button
    {
    public:
        void setButtonEndCallBack( std::function<void( )>const& callback );
    protected:
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
        std::function<void( )> buttonEnd;
    };

    class MainMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class SubMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class Calendar : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( Calendar );
        Calendar* make( );
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
         *  マップを横にスライドするときに使います。
         */
        cocos2d::Vec2 translate;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& path );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void jsonRead( );
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createOptionButton( );
    private:
        /**
         *  jsonデータへのパスを保存します。
         */
        std::string path;

        /**
         * 次の行動目的を表示するためのデータ。
         */
        std::map<std::string, cocos2d::Data> data;

        /**
         *
         */
        Json::Value root;
    };
}

# endif // __LayerCity__
