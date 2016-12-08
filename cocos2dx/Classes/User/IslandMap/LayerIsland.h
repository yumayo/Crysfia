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
        void initData( CityPointData const& scenario ) { *this = scenario; }

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

    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
        cocos2d::ui::Button* createBackButton( );
    };
}

# endif // __LayerIsland__
