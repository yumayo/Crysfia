# ifndef __TextData__
# define __TextData__

# include <deque>
# include <string>
# include <vector>

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
        std::string getLineMoved( );
        bool isEmpty( );
        void makeData( std::string filePath );
    private:
        // 行を作成中にノベルデータとスクリプトデータが混在している行が出てきた場合に、
        // それらを分けて作成したり、コメントが挿入している行や、空行などを排除します。
        void tidydiness( std::string lineString );
        std::deque<std::string> data;
    };
}

# endif // __TextData__