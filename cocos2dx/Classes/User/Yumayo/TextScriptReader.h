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
        // ���@�`�F�b�N
        void syntaxCheck( StringArray const& scriptParts );
    private:
        // �S�Ẵo�b�t�@�[����ɂ��ĕK�v�ȃf�[�^������n���܂��B
        TagWithData getCleanedData( );
        void cleanUp( );
    private:
        // ������Ă����f�[�^�����ƂɁA�X�N���v�g�f�[�^��A�m�x���f�[�^�A�f�o�b�O�f�[�^���l�߂��\���̂����܂��B
        TagWithData tagWithData;
    private:
        // ������Ă����f�[�^���ꎞ�I�ɕۑ����܂��B
        DebugWithLineData debugWithLineData;
    };
}

# endif // __TextScriptReader__
