# ifndef __TextChunk__
# define __TextChunk__

# include "TextTypes.hpp"
# include "TextScriptAnalysis.h"

namespace User
{
    class TextChunk
    {
    public:
        TextChunk( );
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
        FunctionScriptData functionScriptData;
        VariableScriptData variableScriptData;
        NovelData novelData;
        size_t& novelIndex;
    private:
        TextScriptAnalysis scriptAnalysis;
    };
}

# endif // __TextChunk__
