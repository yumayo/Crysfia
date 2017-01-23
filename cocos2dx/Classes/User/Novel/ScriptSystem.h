# ifndef __ScriptSystem__
# define __ScriptSystem__

# include "cocos2d.h"

# include "ScriptBase.h"

# include "TextTypes.hpp"

namespace User
{
    class ScriptSystem : public ScriptBase
    {
    public:
        ScriptSystem( cocos2d::Layer* layer );
        ~ScriptSystem( );
    public:
        void setup( );
    public: // システムの動作を変えるときなどに使います。
        SCRIPT( l ); // シナリオ読み込みをストップ
        SCRIPT( select ); // 選択肢の表示
        SCRIPT( stop );
        SCRIPT( noveldisable );
        SCRIPT( novelenable );
        SCRIPT( novelon );
        SCRIPT( noveloff );
        SCRIPT( novelswitch );
        SCRIPT( item );
        SCRIPT( autosave );
        SCRIPT( heartup );
        SCRIPT( heartdown );
        SCRIPT( heartif );
        SCRIPT( totitle );
        SCRIPT( tobreeding );
        SCRIPT( remove );
        SCRIPT( gameclear );
    public: // 変数の登録に使います。
            // 全てのクラスはシステムを経由してでないと作成できません。
        SCRIPT( name );
        SCRIPT( background );
        SCRIPT( bgm );
        SCRIPT( se );
        SCRIPT( human );
        SCRIPT( still );
        SCRIPT( heart );
        SCRIPT( live2d );
        SCRIPT( voice );
    public:
        cocos2d::Layer* nameLayer = nullptr;
        cocos2d::Layer* humanLayer = nullptr;
        cocos2d::Layer* backgroundLayer = nullptr;
        cocos2d::Layer* selectLayer = nullptr;
        cocos2d::Layer* novelLayer = nullptr;
        cocos2d::Layer* stillLayer = nullptr;
        cocos2d::Layer* heartLayer = nullptr;
        cocos2d::Layer* live2dLayer = nullptr;
        cocos2d::Layer* itemLayer = nullptr;
        cocos2d::Layer* voiceLayer = nullptr;
        cocos2d::Layer* flickFunctionLayer = nullptr;

        /**
         *  現在のメッセージウィンドウの行数を保存しておきます。
         */
        static size_t novelIndex;

        /**
         *  ノベルウィンドウの表示状態を保存しておきます。
         */
        static bool isShowNovel;
    };
}

# endif // __ScriptSystem__
