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
        void insertScript( TagWithData const& tagWithData );
        bool isNext( );
        NovelData getNovelData( );
        void clear( );
    private:
        void makeVariableScript( );
        void makeFunctionScript( );
        void makeNovel( );
        void callFunction( );
    private:
        FunctionScriptChip functionScriptChip;
        FunctionScriptData functionScriptData;
        VariableScriptData variableScriptData;
        size_t& novelIndex;
        NovelData novelData;
    private:
        TagWithData tagWithData;
    };
}

# endif // __TextChank__
