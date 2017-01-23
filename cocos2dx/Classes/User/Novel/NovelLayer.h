# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextLabels.h"
# include "TextChunkManager.h"

# include "../../Lib/json.h"

namespace User
{
    class SwitchBoolean
    {
    public:
        SwitchBoolean( ) : frag( false ) { }
        SwitchBoolean( bool frag ) : frag( frag ) { }
    public:
        void on( ) { frag = true; if ( onCall ) onCall( ); }
        void off( ) { frag = false; if ( offCall ) offCall( ); }
    public:
        std::function<void( )> onCall;
        std::function<void( )> offCall;
        operator bool( ) { return frag; }
        bool operator!( ) { return !frag; }
    private:
        bool frag;
    };

    class NovelReadedPointer : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( NovelReadedPointer );
        NovelReadedPointer* make( );
    };

    class AutoMode : public cocos2d::Node
    {
        float timer = 0.0F;
        std::function<void( )> tick;
    public:
        static AutoMode* create( std::function<void( )> const& tick );
        bool init( std::function<void( )> const& tick );
        void update( float t ) override;
        void stop( );
        void restart( );
    };

    class NovelLayer : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( NovelLayer );
        NovelLayer( std::string const& scenario, std::function<void( )> const& saveCallFunc );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void novelenable( );
        void noveldisable( );
        void on( );
        void off( );
        void stop( );
        void restart( );
    public:
        void skip( );
        void addAuto( );
        void select( std::string const& name );
        void setDelayTime( double delayTime ) { textChunkManager.setDelayTime( delayTime ); }
        // 選択肢でシナリオの読み込み停止機能のスイッチ
        SwitchBoolean systemStop;
        void click( );
        void next( );
        TextChunkManager& getTextChunkManager( ) { return textChunkManager; }
        std::function<void( )> next_scene;

        /**
         * 最後にクリックしたときの画面を保存しておきます。
         */
        static cocos2d::Image* screen;
    private:
        std::function<void( )> saveCallFunc;

        std::string novelPath;
        // 読み込み機能を停止するかどうか。
        // テキストを読み込み途中の場合はtrueになります。
        void readingProceedUpdate( );
        void makeLoadingFeatureOn( );
        void readNextNovel( );
        void textActionStop( );
        // テキストデータを空にする。
        void textClear( );
        // 読み込んだテキストデータをノベルレイヤーに貼り付ける。
        void textPasting( );
        // 読み込みが停止されるまで読み込むかのスイッチ
        SwitchBoolean systemRead;
        // 高速に読み飛ばす機能のスイッチ
        SwitchBoolean readProceed;
        TextLabels textLabels;
        TextChunkManager textChunkManager;

        bool tap_began = false;
        bool long_tap_began = false;
        float tap_time = 0.0F;

        AutoMode* automode = nullptr;

        /**
         *  ノベルを表示をする画像を保存します。
         */
        cocos2d::Sprite* novelWindow = nullptr;
    };
}

# endif // __NovelLayer__
