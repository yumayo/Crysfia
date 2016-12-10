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
    public: // ���̃��C���[��ݒ肷��Ƃ��Ɏg���܂��B
        void SETUP( );
    public: // �V�X�e���̓����ς���Ƃ��ȂǂɎg���܂��B
        // �V�i���I�ǂݍ��݂��X�g�b�v
        void l( );
        // �I�����̕\��
        void select( ArgumentList const& args );
        void stop( ArgumentList const& args );
    public: // �ϐ��̓o�^�Ɏg���܂��B
        void name( ArgumentList const& args );
        void background( ArgumentList const& args );
        void bgm( ArgumentList const& args );
        void se( ArgumentList const& args );
        void human( ArgumentList const& args );
        void still( ArgumentList const& args );
    public:
        cocos2d::Layer* nameLayer = nullptr;
        cocos2d::Layer* humanLayer = nullptr;
        cocos2d::Layer* backgroundLayer = nullptr;
        cocos2d::Layer* selectLayer = nullptr;
        cocos2d::Layer* novelLayer = nullptr;
        cocos2d::Layer* stillLayer = nullptr;

        static size_t novelIndex;
    };
}

# endif // __ScriptSystem__
