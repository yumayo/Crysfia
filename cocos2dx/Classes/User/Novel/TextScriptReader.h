# ifndef __TextScriptReader__
# define __TextScriptReader__

# include "TextTypes.hpp"

namespace User
{
    class TextScriptReader
    {
    public:
        TagWithData createTagWithData( DebugWithLineData const& debugWithLineData );
    private:
        void makeNovelData( );
    private:
        void makeScriptData( );
        // 文法チェック
        void syntaxCheck( StringArray const& scriptParts );
    private:
        // 全てのバッファーを空にして必要なデータだけを渡します。
        TagWithData getCleanedData( );
        void cleanUp( );
    private:
        // もらってきたデータをもとに、スクリプトデータや、ノベルデータ、デバッグデータを詰めた構造体を作ります。
        TagWithData tagWithData;
    private:
        // もらってきたデータを一時的に保存します。
        DebugWithLineData debugWithLineData;
    };
}

# endif // __TextScriptReader__
