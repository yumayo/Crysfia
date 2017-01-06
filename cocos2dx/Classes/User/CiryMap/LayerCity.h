# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

#include "../../Lib/json.h"

namespace User
{
    struct ScenarioPointData
    {
        void initScenarioPointData( Json::Value const& root )
        {
            scenario = root[u8"scenario"].asString( );
            visit = root[u8"visit"].asBool( );
            position = cocos2d::Vec2( root[u8"position"][0].asInt( ),
                                      root[u8"position"][1].asInt( ) );
            title = root[u8"title"].asString( );

            auto& day = root[u8"day"];
            switch ( day.size( ) )
            {
            case 1:
                day_begin = day[0].asInt( );
                day_end = day[0].asInt( );
                break;
            case 2:
                day_begin = day[0].asInt( );
                day_end = day[1].asInt( );
                break;
            default:
                break;
            }

            auto& time = root[u8"time"];
            switch ( time.size( ) )
            {
            case 1:
                time_begin = ( ScenarioPointData::Times )time[0].asInt( );
                time_end = ( ScenarioPointData::Times )time[0].asInt( );
                break;
            case 2:
                time_begin = ( ScenarioPointData::Times )time[0].asInt( );
                time_end = ( ScenarioPointData::Times )time[1].asInt( );
                break;
            default:
                break;
            }
        }

        void initScenarioPointData( ScenarioPointData const& data )
        {
            *this = data;
        }

        /**
         * どういうイベントなのか
         */
        enum Event
        {
            none,
            force,
            main,
            sub
        };
        Event event = none;

        /**
         *  すでに読んだシナリオなのかどうか。
         *  @true   読んでいたら
         *  @false  未読なら
         */
        bool visit = false;

        int day_begin = -1;

        int day_end = -1;

        enum Times
        {
            morning,
            daytime,
            night
        };
        Times time_begin = Times::morning;

        Times time_end = Times::night;

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

    class CityMap;

    class LayerCityMark : protected ScenarioPointData, public cocos2d::ui::Button
    {
    public:
        void setButtonEndCallBack( std::function<void( )>const& callback );
    protected:
        void pasteMap( CityMap* map, ScenarioPointData const& data );
        std::function<void( )> buttonEnd;
    };

    class MainMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( CityMap* map, ScenarioPointData const& data );
    };

    class SubMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( CityMap* map, ScenarioPointData const& data );
    };

    class Calendar : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( Calendar );
        bool init( );
    private:
        /**
         *  カレンダーに表示する日にち。
         */
        int day;
    };

    class CityMap : public cocos2d::Sprite
    {
    public:
        CREATE_ARGS_INIT_FUNC( CityMap );
        bool init( int const x, int const y );
        void paste( cocos2d::ui::Button* icon, int const x, int const y );
        void paste( MainMark* icon, int const x, int const y );
        void paste( SubMark* icon, int const x, int const y );
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

        cocos2d::Size honeycomb_size;
        cocos2d::Vec2 start_position;
        cocos2d::Size map_size;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_INIT_FUNC( LayerCity );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void jsonRead( );
        void time_next( );
        cocos2d::Label* createLabel( std::string const& title );
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createOptionButton( );
        cocos2d::ui::Button* createTimeNextButton( );
    private:
        /**
         *  セーブデータの名前を保存します。
         */
        std::string save_name;

        /**
         * 次の行動目的を表示するためのデータ。
         */
        std::map<std::string, cocos2d::Data> data;

        /**
         *
         */
        Json::Value root;

        void setIslandName( );
    };
}

# endif // __LayerCity__
