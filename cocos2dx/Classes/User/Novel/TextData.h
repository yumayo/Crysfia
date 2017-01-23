# ifndef __TextData__
# define __TextData__

# include <deque>
# include <map>
# include <functional>
# include <string>
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
        void clear( );
        void makeData( std::string fileName );
        void setNextChild( std::string const& selectName );
    private:
        // 行を作成中にノベルデータとスクリプトデータが混在している行が出てきた場合に、
        // それらを分けて作成したり、コメントが挿入している行や、空行などを排除します。
        void tidydiness( std::string lineString, size_t lineNumber );
        // プリプロセッサ命令 sys:import(fileName) の場合のみ、割り込みで別ファイルをリンクします。
        bool isPreprocess( DebugWithLineData const& debugWithLineData );
    private:
        void import( ArgumentList const& args );
        void beginland( ArgumentList const& args );
        void endland( ArgumentList const& args );
    private:
        // makeされたときのファイル名を保存しておきます。
        std::string fileName;
        // ここに、読み込んできたファイルの中身が展開されます。
        TextChankData chunk;
        // 今実行しているデータを指します。
        // チャンクデータは階層構造になっているのでカレントディレクトリを保持します。
        TextChankData* work;
    private:
        // プリプロセスで実行される関数を保存しておきます。
        std::map<std::string, std::function<void( ArgumentList const& )>> preprocess;
    };
}

# endif // __TextData__