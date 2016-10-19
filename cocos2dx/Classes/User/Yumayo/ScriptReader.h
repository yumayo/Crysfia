# ifndef __ScriptReader__
# define __ScriptReader__

# include "TextTypes.hpp"

namespace User
{
    class ScriptReader
    {
    public:
        ScriptReader( );
        ~ScriptReader( );
    public:
        TagRawScriptData createTagRawScriptData( std::string const& lineRawData );
    private:
        void makeNovelData( );
        void makeTagRawScriptData( );
    private:
        static std::string spaceErase( std::string lineStr );
        static std::string commentErase( std::string lineStr );
        static void syntaxCheck( RawScriptPartsData const& rawScriptPartsData );
        TagRawScriptData getCleanedData( );
        void cleanUp( );
    private:
        std::string rawLineData;
        RawScriptPartsData rawScriptPartsData;
        TagRawScriptData tagRawScriptData;
    };
}

# endif // __ScriptReader__
