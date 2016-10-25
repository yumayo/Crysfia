# ifndef __TextScriptReader__
# define __TextScriptReader__

# include "TextTypes.hpp"

namespace User
{
    class TextScriptReader
    {
        friend class TextData;
    public:
        TextScriptReader( );
        ~TextScriptReader( );
    public:
        TagWithData createTagRawScriptPartsData( DebugWithLineData const& debugWithLineData );
    private:
        void makeNovelData( );
        void makeTagRawScriptData( );
    private:
        // 文法チェック
        void syntaxCheck( StringArray const& scriptParts );
        // 全てのバッファーを空にして必要なデータだけを渡します。
        TagWithData getCleanedData( );
        void cleanUp( );
    private:
        ScriptDebugData debugData;

        std::string lineData;
        StringArray scriptParts;

        TagWithData tagWithData;
    };
}

# endif // __TextScriptReader__
