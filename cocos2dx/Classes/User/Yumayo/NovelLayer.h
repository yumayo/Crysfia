# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class NovelLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NovelLayer );
        NovelLayer( );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void setNextChild( std::string const& name );
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
        // 選択肢でシナリオの読み込み停止機能のスイッチ
        void switchIsStopping( ) { isStopping = !isStopping; }
        void textUpdate( );
    private:
        double delayTime = 0.0F; // delayTimeが残っている場合
        // 読み込み機能を停止するかどうか。
        // テキストを読み込み途中の場合はtrueになります。
        bool isSystemRead = true;
        bool isStopping = false; // 選択肢などで読み込みを停止するかどうか。
        bool isReadingProceed = false; // 高速に読み飛ばすかどうか。
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
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        // 高速に読み飛ばす機能のスイッチ
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
