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
        void clear( );
        void makeData( std::string fileName );
        void setNextChild( std::string const& selectName );
    private:
        // �s���쐬���Ƀm�x���f�[�^�ƃX�N���v�g�f�[�^�����݂��Ă���s���o�Ă����ꍇ�ɁA
        // �����𕪂��č쐬������A�R�����g���}�����Ă���s��A��s�Ȃǂ�r�����܂��B
        void tidydiness( std::string lineString, size_t lineNumber );
        // �v���v���Z�b�T���� sys:import(fileName) �̏ꍇ�̂݁A���荞�݂ŕʃt�@�C���������N���܂��B
        bool isPreprocess( DebugWithLineData const& debugWithLineData );
    private:
        void import( ArgumentList const& args );
        void beginland( ArgumentList const& args );
        void endland( ArgumentList const& args );
    private:
        std::string fileName;
        TextChankData chunk;
        TextChankData* work;
    };
}

# endif // __TextData__