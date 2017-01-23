# ifndef __TextString__
# define __TextString__

# include "cocos2d.h"

# include <string>
# include <functional>

namespace User
{
    class TextString
    {
    public:
        TextString( cocos2d::Layer* layer );
        ~TextString( );
    public:
        // 一文字ずつ表示をするときのアクションを設定します。
        // この関数を呼ぶとアクションがスタートします。
        void actionStart( );
        // 一文字ずつ表示をするときのアクションを設定します。
        // この関数を呼ぶとコールバック関数を設定し、アクションがスタートします。
        void actionAndCallfuncStart( std::function<void( )> const& actionCallfunc );
        // アクションを強制的に終わらせます。
        void actionStop( );
        // レイヤーに貼り付け
        void layerPasting( );
        // レイヤーから剥がす
        void layerPeelOff( );
    public:
        void setLabelString( std::string const& text );
        void setDrawPosition( cocos2d::Vec2 position );
    private:
        // 一文字ずつ表示をするときのアクションを設定します。
        // 引数 : 文字列の長さ。
        void setActionStart( size_t stringLength );
    private:
        cocos2d::Layer* layer; // 文字列を貼るレイヤーを持ってきます。
        cocos2d::Label* label; // 文字列を一行描画するため。
        std::string text; // 描画する文字列。
    };
}

# endif // __TextString__
