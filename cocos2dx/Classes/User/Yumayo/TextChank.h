# ifndef __TextChank__
# define __TextChank__

# include "TextTypes.hpp"
# include "TextScriptAnalysis.h"

namespace User
{
    class TextChank
    {
    public:
        TextChank( );
        ~TextChank( );
    public:
        void insertScript( TagWithData const& tagWithData );
        bool isNext( );
        NovelData getNovelData( );
        void clear( );
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

# endif // __TextChank__
