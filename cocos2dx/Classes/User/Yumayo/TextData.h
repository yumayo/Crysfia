# ifndef __TextData__
# define __TextData__

# include <deque>
# include <string>
# include <vector>

# include "TextTypes.hpp"

namespace User
{
    class TextData
    {
    public:
        TextData( );
        ~TextData( );
    public:
        NovelData getNovelDataMoved( );
        std::string getLineMoved( );
    private:
        std::deque<std::string> data;
    };
}

# endif // __TextData__