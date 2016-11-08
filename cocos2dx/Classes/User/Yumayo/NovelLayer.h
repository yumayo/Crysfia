# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class NovelLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NovelLayer );
        NovelLayer( );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void setNextChild( std::string const& name );
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
        // �I�����ŃV�i���I�̓ǂݍ��ݒ�~�@�\�̃X�C�b�`
        void switchIsStopping( ) { isStopping = !isStopping; }
        void textUpdate( );
    private:
        double delayTime = 0.0F; // delayTime���c���Ă���ꍇ
        // �ǂݍ��݋@�\���~���邩�ǂ����B
        // �e�L�X�g��ǂݍ��ݓr���̏ꍇ��true�ɂȂ�܂��B
        bool isSystemRead = true;
        bool isStopping = false; // �I�����Ȃǂœǂݍ��݂��~���邩�ǂ����B
        bool isReadingProceed = false; // �����ɓǂݔ�΂����ǂ����B
        void readingProceedUpdate( );
        void textNextRead( );
        void textActionStop( );
        // delay��0�ł��邩����Asys:l���e�L�X�g���S�Ė��܂�܂œǂݍ��݂܂��B
        void textRead( );
        // �X�N���v�g�����s���ǂݍ���
        void textPartyRead( );
        // �e�L�X�g�f�[�^����ɂ���B
        void textClear( );
        // �ǂݍ��񂾃e�L�X�g�f�[�^���m�x�����C���[�ɓ\��t����B
        void textPasting( );
        // �ǂݍ��݂���~�����܂œǂݍ��ނ��̃X�C�b�`
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        // �����ɓǂݔ�΂��@�\�̃X�C�b�`
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
