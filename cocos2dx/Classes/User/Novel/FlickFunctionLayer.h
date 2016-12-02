# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"

namespace User
{
    class FunctionCircle : public cocos2d::DrawNode
    {
    public:
        CREATE_FUNC( FunctionCircle );
        void drawDot( const cocos2d::Vec2 &pos, float radius, const cocos2d::Color4F &color )
        {
            cocos2d::DrawNode::drawDot( pos, radius, color );
            this->radius = radius;
            this->color = color;
        }
    private:
        cocos2d::Color4F color;
        float radius;
    public:
        cocos2d::Color4F getDrawColor( ) { return color; }
        float getRadius( ) { return radius; }
        cocos2d::Vec2 getWorldPosition( ) { return convertToWorldSpaceAR( cocos2d::Point::ZERO ); }
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
        const float longTapShiftTime = 0.8F;

        /**
         *  ロングタップとみなすかの距離です。
         *  最初にタップした位置からこの時間以上でロングタップではなくなります。
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
        FunctionCircle* circle = nullptr;

        /**
         *  中央のサークルの半径です。
         */
        const float circleRadius = 100.0F;

        /**
         *  サブメニューサークルの半径です。
         */
        const float subMenuRadius = 60.0F;

        /**
         *  Novelレイヤーを保存します。
         *  メニューを出したら、Novelレイヤーのタッチイベントを無効にするためです。
         */
        cocos2d::Layer* novelLayer = nullptr;
    };
}

# endif // __FlickFunctionLayer__
