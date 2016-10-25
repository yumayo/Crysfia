# ifndef __TextTypes__
# define __TextTypes__

# include <array>
# include <string>
# include <vector>
# include <map>

namespace User
{
    enum class Tag
    {
        Null = 0,
        Start = 1000,
        System,
        Background,
        Human,
        Novel,
        Name,
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
    using VariableScriptData = std::map<std::string, std::string>;
    using ArgumentList = StringArray;

    struct FunctionInfo
    {
        std::string name;
        ArgumentList argumentList;
    };
    using FunctionScriptData = std::map<std::string, FunctionInfo>;
    struct FunctionScriptChip
    {
        std::string variable;
        FunctionInfo functionInfo;
    };
}

# endif // __TextTypes__
