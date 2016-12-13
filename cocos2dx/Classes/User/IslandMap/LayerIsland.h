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

    class LayerIslandMark : protected CityPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class CityMark : public LayerIslandMark
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

        /**
        *  今の時間。
        */
        enum Times
        {
            morning,
            daytime,
            night
        };
    private:
        Islands islands = Islands::none;

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
    private:
        void movePoint( cocos2d::Sprite* map, cocos2d::Vec2 start, cocos2d::Vec2 end, std::string path );
    };
}

# endif // __LayerIsland__
