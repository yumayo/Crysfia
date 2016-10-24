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
        TagWithNovelStringAndRawScriptPartsData createTagRawScriptPartsData( std::string const& lineRawData, std::string const& line );
    private:
        void makeNovelData( );
        void makeTagRawScriptData( );
    private:
        // 文法チェック
        static void syntaxCheck( RawScriptPartsData const& rawScriptPartsData );
        // 全てのバッファーを空にして必要なデータだけを渡します。
        TagWithNovelStringAndRawScriptPartsData getCleanedData( );
        void cleanUp( );
    private:
        std::string rawLineData;
        RawScriptPartsData rawScriptPartsData;
        TagWithNovelStringAndRawScriptPartsData tagWithNovelStringAndRawScriptPartsData;
    };
}

# endif // __TextScriptReader__
