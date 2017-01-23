# ifndef __ScriptHeart__
# define __ScriptHeart__

# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "ScriptBase.h"

namespace User
{
    /**
     *  親愛度ゲージクラス
     *  主な使い方 HeartGauge::create()->make()
     *  上記のように記入すると、画面左上に設定されたノードが返ってきます。
     *  そのままレイヤーに貼り付けましょう。
     */
    class HeartGauge : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( HeartGauge );
        /**
         *  親愛度ゲージを作成します。
         *  表示位置は画面の左上です。
         *  アンカーポイントは画像の左上です。
         *  この関数を呼んだときに、親愛度は自動的にロードします。
         */
        HeartGauge* make( );
    public:
        /**
         *  現在の親愛度を返します。
         */
        int getValue( ) { return now; }

        /**
         *  ゲージの量を増やします。
         *  < value >に自然数を入れると作動します。
         *  一秒間で現在の数値から< value >分上がります。
         *  中でセーブも自動的に行われます。
         */
        HeartGauge* up( int value );

        /**
         *  ゲージの量を増やします。
         *  < value >に自然数を入れると作動します。
         *  一秒間で現在の数値から< value >分下がります。
         *  中でセーブも自動的に行われます。
         */
        HeartGauge* down( int value );

        /**
         *  スクリプト用のアクションを開始します。
         *  自動で削除を行います。
         *  < str >には文字列で数値代入できます。
         *  < str="10" >のように使えます。
         */
        HeartGauge* scriptUpAction( std::string const& str );

        /**
         *  スクリプト用のアクションを開始します。
         *  自動で削除を行います。
         *  < str >には文字列で数値代入できます。
         *  < str="10" >のように使えます。
         */
        HeartGauge* scriptDownAction( std::string const& str );
    private:
        int max = 200;
        int now = 0;
        cocos2d::Size size;
        int start = 0;
        int end = 0;
        int getWidth( int value );
        cocos2d::Sprite* background = nullptr;
    private:
        cocos2d::FiniteTimeAction* createValueAction( int value );
        cocos2d::Sequence* createInValueStopOutExitAction( int value );
    };

    class ScriptHeart : public ScriptBase
    {
    public:
        ScriptHeart( cocos2d::Layer* layer );
    public:
        SCRIPT( up );
        SCRIPT( down );
    };
}

# endif // __ScriptHeart__
