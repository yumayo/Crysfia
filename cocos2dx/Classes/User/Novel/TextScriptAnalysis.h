# ifndef __TextScriptAnalysis__
# define __TextScriptAnalysis__

# include "TextTypes.hpp"

namespace User
{
    class TextScriptAnalysis
    {
    public:
        void makeScript( TagWithData const& tagWithData );
        void clear( );
    public:
        TagWithData::Tag const& getTag( ) const { return tagWithData.tag; }
        NovelScript const& getNovelScript( ) const { return novelScript; }
        FunctionScript const& getFunctionScript( ) const { return functionScript; }
        VariableScript  const& getVariableScript( )  const { return variableScript; }
        TagWithData const& getTagWithData( ) const { return tagWithData; }
    private:
        void makeVariableScript( );
        void makeFunctionScript( );
        void makeNovelScript( );
    private:
        NovelScript novelScript;
        FunctionScript functionScript;
        VariableScript variableScript;
        // もらってきたデータを一時的に保存します。
        TagWithData tagWithData;
    };
}

# endif // __TextScriptAnalysis__
