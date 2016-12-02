# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextLabels.h"
# include "TextChunkManager.h"

namespace User
{
    class SwitchBoolean
    {
    public:
        SwitchBoolean( ) : frag( false ) { }
        SwitchBoolean( bool frag ) : frag( frag ) { }
    public:
        void on( ) { frag = true; }
        void off( ) { frag = false; }
    public:
        operator bool( ) { return frag; }
        bool operator!( ) { return !frag; }
    private:
        bool frag;
    };

    class NovelLayer : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( NovelLayer );
        NovelLayer( std::string const& novelPath );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void on( );
        void off( );
    public:
        void select( std::string const& name );
        void setDelayTime( double delayTime ) { textChunkManager.setDelayTime( delayTime ); }
        // �I�����ŃV�i���I�̓ǂݍ��ݒ�~�@�\�̃X�C�b�`
        SwitchBoolean systemStop;
        void click( );
        TextChunkManager& getTextChunkManager( ) { return textChunkManager; }
    private:
        std::string novelPath;
        // �ǂݍ��݋@�\���~���邩�ǂ����B
        // �e�L�X�g��ǂݍ��ݓr���̏ꍇ��true�ɂȂ�܂��B
        void readingProceedUpdate( );
        void makeLoadingFeatureOn( );
        void readNextNovel( );
        void textActionStop( );
        // �e�L�X�g�f�[�^����ɂ���B
        void textClear( );
        // �ǂݍ��񂾃e�L�X�g�f�[�^���m�x�����C���[�ɓ\��t����B
        void textPasting( );
        // �ǂݍ��݂���~�����܂œǂݍ��ނ��̃X�C�b�`
        SwitchBoolean systemRead;
        // �����ɓǂݔ�΂��@�\�̃X�C�b�`
        SwitchBoolean readProceed;
        TextLabels textLabels;
        TextChunkManager textChunkManager;
    };
}

# endif // __NovelLayer__
