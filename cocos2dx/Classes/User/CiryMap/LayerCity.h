# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct ScenarioPointData
    {
        /**
         *  �f�[�^�̏��������s���܂��B
         *  �\���ɕK�v�ȃf�[�^�����l�߂܂��B
         */
        void initData( bool isChecked, cocos2d::Vec2 const& position, std::string const& scenario )
        {
            this->isChecked = isChecked;
            this->position = position;
            this->scenario = scenario;
        }

        /**
         *  �f�[�^�̏��������s���܂��B
         *  �R�s�[������Ă��̂܂ܑ�����܂��B
         */
        void initData( ScenarioPointData const& scenario ) { *this = scenario; }

        /**
         *  ���łɓǂ񂾃V�i���I�Ȃ̂��ǂ����B
         *  @true   �ǂ�ł�����
         *  @false  ���ǂȂ�
         */
        bool isChecked;

        /**
         *  �}�b�v�摜���̕\���ʒu�B
         */
        cocos2d::Vec2 position;

        /**
         *  �ǂݍ��ރV�i���I�t�@�C���̃p�X�B
         */
        std::string scenario;
    };

    class Mark : protected ScenarioPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class MainMark : public Mark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class SubMark : public Mark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class Calendar : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( Calendar );
        Calendar* make( );
    private:
        /**
         *  �J�����_�[�ɕ\��������ɂ��B
         */
        int day;
    };

    class CityMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( CityMap );
        CityMap* make( std::string const& backgroundfile );
    private:
        /**
         *  ���̎��ԁB
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
        Times times;

        /**
         *  �摜���E�B���h�E�̏c�Ɏ��߂邽�߂̃X�P�[���ł��B
         *  ���̃X�P�[�����|����Ɖ摜���c��ʂɃs�b�^�����܂�܂��B
         */
        float backgroundWindowHeightFitScale;

        /**
         *  �}�b�v�����ɃX���C�h����Ƃ��Ɏg���܂��B
         */
        cocos2d::Vec2 translate;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& backgroundPath );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        cocos2d::ui::Button* createBackButton( );
    private:
        std::string backgroundPath;

        /**
         * ���̍s���ړI��\�����邽�߂̃f�[�^�B
         */
        std::map<std::string, cocos2d::Data> data;
    };
}

# endif // __LayerCity__
