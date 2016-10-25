# ifndef __TextData__
# define __TextData__

# include <deque>
# include "TextTypes.hpp"

namespace User
{
    void spaceErase( std::string& lineString );
    void commentErase( std::string& lineString );
    void alignFirst( std::string& lineString );

    class TextData
    {
    public:
        TextData( );
        ~TextData( );
    public:
        DebugWithLineData getLineMoved( );
        bool isEmpty( );
        void makeData( std::string fileName );
    private:
        // 行を作成中にノベルデータとスクリプトデータが混在している行が出てきた場合に、
        // それらを分けて作成したり、コメントが挿入している行や、空行などを排除します。
        void tidydiness( std::string lineString, size_t lineNumber );
        std::deque<DebugWithLineData> data;
        std::string fileName;
    };
}

# endif // __TextData__