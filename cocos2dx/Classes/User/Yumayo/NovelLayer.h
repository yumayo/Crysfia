# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class SwitchBoolean
    {
    public:
        SwitchBoolean( ) : frag( false ) { }
        SwitchBoolean( bool frag ) : frag( frag ) { }
    public:
        void on( ) { frag = true; }
        void off( ) { frag = false; }
    public:
        operator bool( ) { return frag; }
        bool operator!( ) { return !frag; }
    private:
        bool frag;
    };

    class NovelLayer : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( NovelLayer );
        NovelLayer( std::string const& novelPath );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void on( );
        void off( );
    public:
        void setNextChild( std::string const& name );
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
        // 選択肢でシナリオの読み込み停止機能のスイッチ
        SwitchBoolean systemStop;
        void textUpdate( );
    private:
        std::string novelPath;
        double delayTime = 0.0F; // delayTimeが残っている場合
        // 読み込み機能を停止するかどうか。
        // テキストを読み込み途中の場合はtrueになります。
        void readingProceedUpdate( );
        void textNextRead( );
        void textActionStop( );
        // delayが0であるかぎり、sys:lかテキストが全て埋まるまで読み込みます。
        void textRead( );
        // スクリプトから一行分読み込む
        void textPartyRead( );
        // テキストデータを空にする。
        void textClear( );
        // 読み込んだテキストデータをノベルレイヤーに貼り付ける。
        void textPasting( );
        // 読み込みが停止されるまで読み込むかのスイッチ
        SwitchBoolean systemRead;
        // 高速に読み飛ばす機能のスイッチ
        SwitchBoolean readProceed;
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
