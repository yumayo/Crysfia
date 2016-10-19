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
        TextString = 1003
    };
    constexpr uint32_t lineSize = 3U;
    using NovelData = std::array<std::string, lineSize>;
    using RawScriptPartsData = std::vector<std::string>;

    struct TagRawScriptData
    {
        enum class Tag
        {
            NIL,
            NOV,
            VAR,
            FUN,
        };
        Tag tag;
        RawScriptPartsData data;
    };
    using VariableScriptData = std::map<std::string, std::string>;
    using ArgumentList = std::vector<std::string>;

    struct FunctionScript
    {
        std::string name;
        ArgumentList argumentList;
    };
    using FunctionScriptData = std::map<std::string, FunctionScript>;
    struct FunctionScriptChip
    {
        std::string variable;
        FunctionScript functionInfo;
    };
}

# endif // __TextTypes__
