# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"

namespace User
{
    class Menu : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( Menu );
        Menu( ) { }
        ~Menu( ) { }
        std::function<void( )> menuCallBack;
    private:
        bool onTouch = false;
        bool prevOnTouch = false;
    public:
        void update( bool touch );
        bool isHit( cocos2d::Vec2 touchPos );
        bool isIn( );
        bool isStay( );
        bool isOut( );
    public:
        static float circleRadius;
        static int maxMenuNumber;
    };

    class FlickFunctionLayer : public LayerBase
    {
    public:
        CREATE_FUNC( FlickFunctionLayer );
        FlickFunctionLayer( );
        ~FlickFunctionLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        void began( cocos2d::Touch* touch );
        void moved( cocos2d::Touch* touch );
        void ended( cocos2d::Touch* touch );
        void createFlickCircle( );
    private:
        /**
         *  �����O�^�b�v�Ȃ�utrue�v
         *  �����łȂ��Ȃ�uflase�v
         */
        bool isLongTap( ) { return isTap && isSuccessLongTap && ( longTapShiftTime <= holdTapTime ); }

        /**
         *  �����O�^�b�v�Ńt�@���N�V�������Ăяo���Ă���Ƃ��Ɂutrue�v�ɂȂ�܂��B
         *  �\�����\���ɐ؂�ւ��Ƃ��̃��[�V�������ƕ\������Ă��Ȃ��Ƃ��́ufalse�v�ɂȂ�܂��B
         *  �����ɋ@�\���g����Ƃ��̂݁utrue�v�ɂȂ�܂��B
         */
        bool isFunction = false;

        /**
         *  �^�b�v���Ă���Ԃ́utrue�v�ɂȂ�܂��B
         */
        bool isTap = false;

        /**
         *  �����O�^�b�v������������utrue�v�ɂȂ�܂��B
         */
        bool isSuccessLongTap = false;

        /**
         *  �^�b�v���Ă��鎞�Ԃ�ۑ����܂��B
         */
        float holdTapTime = 0.0F;

        /**
         *  �����O�^�b�v�Ɉڍs����܂ł̎��Ԃł��B
         *  < holdTapTime > �����̎��Ԉȏ�Ń����O�^�b�v�����ɂȂ�܂��B
         */
        const float longTapShiftTime = 0.4F;

        /**
         *  �����O�^�b�v�Ƃ݂Ȃ����̋����ł��B
         *  �ŏ��Ƀ^�b�v�����ʒu���炱�̋������������ɗ����ƃ����O�^�b�v�ł͂Ȃ��Ȃ�܂��B
         */
        const float longTapShiftLength = 50.0F;

        /**
         *  �^�b�v�����u�Ԃ̏ꏊ��ۑ����Ă����܂��B
         */
        cocos2d::Vec2 tapBeganPosition;

        /**
         *  �Ō�ɐG�����ꏊ��ۑ����Ă����܂��B
         *  �^�b�v���Ă���Ԃɏꏊ�̕ύX���������ꍇ�͂��̒l�ɕς��܂��B
         */
        cocos2d::Vec2 tapLastPosition;

        /**
         *  �����̃T�[�N���̃|�C���^��ۑ����Ă����܂��B
         */
        cocos2d::Node* circle = nullptr;

        /**
         *  ���j���[�܂ł̋����ł��B
         */
        const float menuLength = 100.0F;

        /**
         *  ���j���[�̔��a�ł��B
         */
        const float menuCircleRadius = 80.0F;

        /**
         *  ���j���[�̐��ł��B
         */
        const int numberMenu = 4;

        /**
         *  Novel���C���[��ۑ����܂��B
         *  ���j���[���o������ANovel���C���[�̃^�b�`�C�x���g�𖳌��ɂ��邽�߂ł��B
         */
        cocos2d::Layer* novelLayer = nullptr;

        /**
         *  �o�b�O���O���C���[��ۑ����܂��B
         *  �T�[�N���̋@�\�Ƃ��Ďg�����߂ł��B
         */
        cocos2d::Layer* baglogLayer = nullptr;

        /**
         *  ���j���[�̋@�\��ǉ����܂��B
         */
        void addMenu( std::string name, std::function<void( )> const& lambda );
    };
}

# endif // __FlickFunctionLayer__
