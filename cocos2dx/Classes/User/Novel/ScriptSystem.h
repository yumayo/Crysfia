# ifndef __ScriptSystem__
# define __ScriptSystem__

# include "cocos2d.h"

# include "ScriptBase.h"

# include "TextTypes.hpp"

namespace User
{
    class ScriptSystem : public ScriptBase
    {
    public:
        ScriptSystem( cocos2d::Layer* layer );
        ~ScriptSystem( );
    public:
        void setup( );
    public: // �V�X�e���̓����ς���Ƃ��ȂǂɎg���܂��B
        SCRIPT( l ); // �V�i���I�ǂݍ��݂��X�g�b�v
        SCRIPT( select ); // �I�����̕\��
        SCRIPT( stop );
        SCRIPT( novelon );
        SCRIPT( noveloff );
        SCRIPT( novelswitch );
    public: // �ϐ��̓o�^�Ɏg���܂��B
            // �S�ẴN���X�̓V�X�e�����o�R���ĂłȂ��ƍ쐬�ł��܂���B
        SCRIPT( name );
        SCRIPT( background );
        SCRIPT( bgm );
        SCRIPT( se );
        SCRIPT( human );
        SCRIPT( still );
        SCRIPT( heart );
        SCRIPT( live2d );
    public:
        cocos2d::Layer* nameLayer = nullptr;
        cocos2d::Layer* humanLayer = nullptr;
        cocos2d::Layer* backgroundLayer = nullptr;
        cocos2d::Layer* selectLayer = nullptr;
        cocos2d::Layer* novelLayer = nullptr;
        cocos2d::Layer* stillLayer = nullptr;
        cocos2d::Layer* heartLayer = nullptr;
        cocos2d::Layer* live2dLayer = nullptr;

        /**
         *  ���݂̃��b�Z�[�W�E�B���h�E�̍s����ۑ����Ă����܂��B
         */
        static size_t novelIndex;

        /**
         *  �m�x���E�B���h�E�̕\����Ԃ�ۑ����Ă����܂��B
         */
        static bool isShowNovel;
    };
}

# endif // __ScriptSystem__
