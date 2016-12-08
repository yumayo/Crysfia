# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"

namespace User
{
    class Menu : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( Menu );
        Menu( ) { }
        ~Menu( ) { }
        std::function<void( )> menuCallBack;
    private:
        bool onTouch = false;
        bool prevOnTouch = false;
    public:
        void update( bool touch );
        bool isHit( cocos2d::Vec2 touchPos );
        bool isIn( );
        bool isStay( );
        bool isOut( );
    public:
        static float circleRadius;
        static int maxMenuNumber;
    };

    class FlickFunctionLayer : public LayerBase
    {
    public:
        CREATE_FUNC( FlickFunctionLayer );
        FlickFunctionLayer( );
        ~FlickFunctionLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        void began( cocos2d::Touch* touch );
        void moved( cocos2d::Touch* touch );
        void ended( cocos2d::Touch* touch );
        void createFlickCircle( );
    private:
        /**
         *  ロングタップなら「true」
         *  そうでないなら「flase」
         */
        bool isLongTap( ) { return isTap && isSuccessLongTap && ( longTapShiftTime <= holdTapTime ); }

        /**
         *  ロングタップでファンクションを呼び出しているときに「true」になります。
         *  表示や非表示に切り替わるときのモーション中と表示されていないときは「false」になります。
         *  純粋に機能を使えるときのみ「true」になります。
         */
        bool isFunction = false;

        /**
         *  タップしている間は「true」になります。
         */
        bool isTap = false;

        /**
         *  ロングタップが成功したら「true」になります。
         */
        bool isSuccessLongTap = false;

        /**
         *  タップしている時間を保存します。
         */
        float holdTapTime = 0.0F;

        /**
         *  ロングタップに移行するまでの時間です。
         *  < holdTapTime > がこの時間以上でロングタップ扱いになります。
         */
        const float longTapShiftTime = 0.4F;

        /**
         *  ロングタップとみなすかの距離です。
         *  最初にタップした位置からこの距離よりも遠くに離れるとロングタップではなくなります。
         */
        const float longTapShiftLength = 50.0F;

        /**
         *  タップした瞬間の場所を保存しておきます。
         */
        cocos2d::Vec2 tapBeganPosition;

        /**
         *  最後に触った場所を保存しておきます。
         *  タップしている間に場所の変更があった場合はその値に変わります。
         */
        cocos2d::Vec2 tapLastPosition;

        /**
         *  中央のサークルのポインタを保存しておきます。
         */
        cocos2d::Node* circle = nullptr;

        /**
         *  メニューまでの距離です。
         */
        const float menuLength = 100.0F;

        /**
         *  メニューの半径です。
         */
        const float menuCircleRadius = 80.0F;

        /**
         *  メニューの数です。
         */
        const int numberMenu = 4;

        /**
         *  Novelレイヤーを保存します。
         *  メニューを出したら、Novelレイヤーのタッチイベントを無効にするためです。
         */
        cocos2d::Layer* novelLayer = nullptr;

        /**
         *  バッグログレイヤーを保存します。
         *  サークルの機能として使うためです。
         */
        cocos2d::Layer* baglogLayer = nullptr;

        /**
         *  メニューの機能を追加します。
         */
        void addMenu( std::string name, std::function<void( )> const& lambda );
    };
}

# endif // __FlickFunctionLayer__
