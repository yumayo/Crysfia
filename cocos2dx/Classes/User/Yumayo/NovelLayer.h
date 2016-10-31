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

        void textUpdate( float delta );
        // スクリプトから一行分読み込む
        void textPartyUpdate( );
        // テキストデータを空にする。
        void textClear( );
        // 読み込んだテキストデータをノベルレイヤーに貼り付ける。
        void textPasting( );
        // 読み込みが停止されるまで読み込むかのスイッチ
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        // 選択肢でシナリオの読み込み停止機能のスイッチ
        void switchIsSelectStopping( ) { isSelectStopping = !isSelectStopping; }
        // 高速に読み飛ばす機能のスイッチ
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
    private:
        double delayTime = 0.0F; // delayTimeが残っている場合
        bool isSystemRead = true; 
        bool isSelectStopping = true; // 選択肢などで読み込みを停止するかどうか。
        bool isReadingProceed = false; // 高速に読み飛ばすかどうか。
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
