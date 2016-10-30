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
        void textUpdate( );
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        void switchIsNextText( ) { isNextText = !isNextText; }
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
    private:
        double delayTime = 0.0F; // delayTimeが残っている場合
        bool isSystemRead = false; // sys:lか3行を読み込むまで飛ばすか。
        bool isNextText = true; // 選択肢などで読み込みを停止するかどうか。
        bool isReadingProceed = false; // 高速に読み飛ばすかどうか。
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
