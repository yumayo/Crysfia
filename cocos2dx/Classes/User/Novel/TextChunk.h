# ifndef __TextChunk__
# define __TextChunk__

# include "TextTypes.hpp"
# include "TextScriptAnalysis.h"

namespace User
{
    class TextChunkManager;
    class TextChunk
    {
    public:
        TextChunk( TextChunkManager* manager );
        ~TextChunk( );
    public:
        void insertScript( TagWithData const& tagWithData );
        bool isReadFinished( );
        NovelData const& getNovelData( );
    private:
        void pushVariable( );
        void pushFunction( );
        void pushNovel( );
    private:
        TextChunkManager* manager;
        FunctionScriptData functionScriptData;
        NovelData novelData;
        size_t& novelIndex;
    private:
        TextScriptAnalysis scriptAnalysis;
    };
}

# endif // __TextChunk__
