# ifndef __TextChank__
# define __TextChank__

# include "TextTypes.hpp"

namespace User
{
    class TextChank
    {
    public:
        TextChank( );
        ~TextChank( );
    public:
        void insertScript( TagRawScriptData const& tagRawScriptData );
        bool isNext( );
        NovelData getNovelData( );
        void clear( );
        FunctionScriptData getFunctionScript( );
    private:
        void makeVariableScript( );
        void makeFunctionScript( );
        void makeNovel( );
    private:
        FunctionScriptData functionScriptData;
        VariableScriptData variableScriptData;
        size_t novelIndex = 0;
        NovelData novelData;
    private:
        TagRawScriptData bufferTagRawScriptData;
    };
}

# endif // __TextChank__
