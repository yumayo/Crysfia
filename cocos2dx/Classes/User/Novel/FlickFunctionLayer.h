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
         *  タップしている時間を保存します。
         */
        float holdTapTime = 0.0F;

        /**
         *  ロングタップに移行するまでの時間です。
         *  < holdTapTime > がこの時間を超えるとロングタップ扱いになります。
         */
        const float longTapShiftTime = 0.8F;

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
         *  ロングタップが成功した場合に「true」になります。
         */
        bool isLongTap = false;

        /**
         *  中央のサークルのポインタを保存しておきます。
         */
        FunctionCircle* circle = nullptr;
    };
}

# endif // __FlickFunctionLayer__
