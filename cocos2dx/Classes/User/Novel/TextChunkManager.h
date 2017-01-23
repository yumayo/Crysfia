# ifndef __TextChunkManager__
# define __TextChunkManager__

# include "cocos2d.h"

# include "TextData.h"
# include "TextScriptReader.h"
# include "TextChunk.h"

# include <functional>

namespace User
{
    class TextChunkManager
    {
    public:
        TextChunkManager( );
        ~TextChunkManager( );
    public:
        bool isNovelFinished( );
        void make( std::string const& novelPath );
        void select( std::string const& selectName );
        void textRead( );
        NovelData const& getNovelData( );
        std::vector<TextChunk> const& getTextChunk( );
        void updateDelay( float delta );
        void setDelayTime( double delay );
        void gotoNext( );
        std::function<void( )> novelEndCallBack = nullptr;
        std::function<void( )> readEndCallBack = nullptr;
    private:
        bool textPartyRead( );
    private:
        double delayTime = 0.0F;
        TextData textData;
        TextScriptReader textReader;

        // 変数データはマネージャーが持ちます。
        VariableScriptData variableScriptData;
        friend class TextChunk;
        std::vector<TextChunk> textChunk;
        TextChunk* work;
    };
}

# endif // __TextChunkManager__
