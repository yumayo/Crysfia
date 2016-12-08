# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct CityPointData
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
        void initData( CityPointData const& scenario ) { *this = scenario; }

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

    class Mark : protected CityPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class CityMark : public Mark
    {
    public:
        CREATE_FUNC( CityMark );
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class IslandMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( IslandMap );
        IslandMap* make( );
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

    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
        cocos2d::ui::Button* createBackButton( );
    };
}

# endif // __LayerIsland__
