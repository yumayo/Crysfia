# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"
# include "ui/CocosGUI.h"

namespace User
{
    class Functions : public cocos2d::ui::Layout
    {
    public:
        CREATE_ARGS_FUNC( Functions );
    public:
        Functions( std::vector<std::pair<std::string, std::function<void( )>>> functions );
        int icon_size;
        void begin( );
        void cancel( );
        void end( );
        std::function<void( )> ended;
        std::function<void( )> canceled;
    private:
    };

    class FlickFunctionLayer : public LayerBase
    {
    public:
        CREATE_FUNC( FlickFunctionLayer );
        FlickFunctionLayer( );
        ~FlickFunctionLayer( );
        bool init( ) override;
        void setup( ) override;
        void end( );
    private:
        void createFlickCircle( );
    private:
        /**
         *  Novelレイヤーを保存します。
         *  メニューを出したら、Novelレイヤーのタッチイベントを無効にするためです。
         */
        cocos2d::Layer* novelLayer = nullptr;

        /**
         *  バッグログレイヤーを保存します。
         *  サークルの機能として使うためです。
         */
        cocos2d::Layer* backlogLayer = nullptr;

        /**
         * ネームレイヤーを保存します。
         * ノベルウィンドウの非表示状態の機能を扱うためです。
         */
        cocos2d::Layer* nameLayer = nullptr;


        Functions* functions = nullptr;
    };
}

# endif // __FlickFunctionLayer__
