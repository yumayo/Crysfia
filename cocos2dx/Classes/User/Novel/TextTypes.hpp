# ifndef __TextTypes__
# define __TextTypes__

# include <array>
# include <string>
# include <vector>
# include <map>
# include <deque>
# include <memory>

namespace User
{
    enum class Tag
    {
        Null = 0,
        Start = 1000,
        Background,
        Still,
        Human,
        Live2d,
        Novel,
        Name,
        Heart,
        Select,
        ItemLayer,
        FlickFunction,
        BackLog,
        System,
    };
    constexpr uint32_t lineSize = 3U;
    using NovelData = std::array<std::string, lineSize>;
    using StringArray = std::vector<std::string>;

    struct ScriptDebugData
    {
        size_t lineNumber;
        std::string fileName;
    };

    struct DebugWithLineData
    {
        ScriptDebugData debugData;
        std::string lineData;
    };

    using DequeScriptChunk = std::deque<DebugWithLineData>;

    class TextChankData
    {
    public:
        TextChankData( ) { }
        TextChankData( TextChankData* pointer ) : parentPointer( pointer ) { }
        TextChankData* parentPointer = nullptr;
        std::map<std::string, TextChankData> children;
        DequeScriptChunk data;
    };

    struct TagWithData
    {
        enum class Tag
        {
            NIL,
            NOV,
            VAR,
            FUN,
        };
        Tag tag;
        ScriptDebugData debugData;
        StringArray scriptParts;
        std::string novel;
    };

    using ArgumentList = StringArray;

    struct FunctionInfo
    {
        std::string name;
        ArgumentList argumentList;
    };

    struct NovelScript
    {
        std::string novel;
    };
    struct VariableScript
    {
        std::string variable;
        std::string currentStatus;
    };
    struct FunctionScript
    {
        std::string variable;
        FunctionInfo functionInfo;
    };

    void errorSStream( std::string const& error, ScriptDebugData const& debugData );

    using VariableScriptData = std::map<std::string, std::string>;
    using FunctionScriptData = std::map<std::string, FunctionInfo>;
}

# endif // __TextTypes__
