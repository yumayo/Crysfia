# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

#include "../../Lib/json.h"

namespace User
{
    struct ScenarioPointData
    {
        void initScenarioPointData( Json::Value const& root );

        bool is_stay( ) const;

        int get_dead_line( ) const;

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

        /**
         * マップに配置されたかを保存します。
         * @true    配置されていたら
         * @false   配置されていないなら
         */
        bool spawn = false;

        bool read_not = false;

        int day_begin = -1;

        int day_end = -1;

        enum class Times
        {
            none,
            morning,
            daytime,
            night,
        };
        bool morning = true;
        bool daytime = true;
        bool night = true;

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

    class CityMap : public cocos2d::Layer
    {
    public:
        CREATE_ARGS_INIT_FUNC( CityMap );
        bool init( );
        void paste( cocos2d::ui::Button* icon, int const x, int const y );
        void paste( MainMark* icon, int const x, int const y );
        void paste( SubMark* icon, int const x, int const y );
        cocos2d::MoveTo* move_action( int const x, int const y );
        void set_position( int const x, int const y );
        void set_enable( );
        void set_disable( );
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

        cocos2d::Sprite* map;

        cocos2d::Layer* move_layer;

        bool is_move = false;

        cocos2d::EventListenerTouchOneByOne* event = nullptr;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_INIT_FUNC( LayerCity );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void jsonRead( );
        void json_read_game_clear( );
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

        bool force_event = false;

        void setIslandName( );

        LayerCityMark* set_force_mark( Json::Value& value );
        LayerCityMark* set_main_mark( Json::Value& value );
        LayerCityMark* set_sub_mark( Json::Value& value );

        CityMap* map = nullptr;

        bool is_animation = true;
        void animation_start( );
        void animation_end( );

        // 新しく生まれてくるシナリオのチェック。
        std::stack<std::function<void( )>> mark_stack;
        std::stack<cocos2d::Vec2> mark_pos_stack;
        void stack_mark_pos( Json::Value& value );
        void event_recovery( );
        void event_recovery_skip( );

        // 期限を過ぎて読めなくなるシナリオのチェック。
        std::stack<std::function<void( )>> mark_ptr_stack;
        std::stack<cocos2d::Vec2> mark_ptr_pos_stack;
        void stack_mark_ptr_pos( Json::Value& value );
        void read_check( );
        void read_check_skip( );
    };
}

# endif // __LayerCity__
