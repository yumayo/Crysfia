# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct CityPointData
    {
        /**
         *  データの初期化を行います。
         *  構造に必要なデータを一つ一つ詰めます。
         */
        void initData( cocos2d::Vec2 const& position, std::string const& path )
        {
            this->position = position;
            this->path = path;
        }

        /**
         *  データの初期化を行います。
         *  コピーを取ってそのまま代入します。
         */
        void initData( CityPointData const& scenario ) { *this = scenario; }

        /**
         *  マップ画像中の表示位置。
         */
        cocos2d::Vec2 position;

        /**
         *  島の情報。
         */
        std::string path;
    };

    class Mark : protected CityPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class CityMark : public Mark
    {
    public:
        CREATE_FUNC( CityMark );
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class IslandMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( IslandMap );
        IslandMap* make( );
    private:
        /**
         *  滞在中の島
         */
        enum Islands
        {
            none,
            first,
            second,
            third,
            forth,
            fifth,
        };
        Islands islands = Islands::none;

        /**
         *  今の時間。
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
        Times times = Times::morning;

        /**
         *  マップを横にスライドするときに使います。
         */
        cocos2d::Vec2 translate;
    };

    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __LayerIsland__
