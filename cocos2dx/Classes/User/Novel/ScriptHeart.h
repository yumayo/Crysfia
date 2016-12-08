# ifndef __ScriptHeart__
# define __ScriptHeart__

# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "ScriptBase.h"

namespace User
{
    /**
     *  �e���x�Q�[�W�N���X
     *  ��Ȏg���� HeartGauge::create()->make()
     *  ��L�̂悤�ɋL������ƁA��ʍ���ɐݒ肳�ꂽ�m�[�h���Ԃ��Ă��܂��B
     *  ���̂܂܃��C���[�ɓ\��t���܂��傤�B
     */
    class HeartGauge : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( HeartGauge );
        /**
         *  �e���x�Q�[�W���쐬���܂��B
         *  �\���ʒu�͉�ʂ̍���ł��B
         *  �A���J�[�|�C���g�͉摜�̍���ł��B
         *  ���̊֐����Ă񂾂Ƃ��ɁA�e���x�͎����I�Ƀ��[�h���܂��B
         */
        HeartGauge* make( );
    public:
        /**
         *  ���݂̐e���x��Ԃ��܂��B
         */
        int getValue( ) { return now; }

        /**
         *  �Q�[�W�̗ʂ𑝂₵�܂��B
         *  < value >�Ɏ��R��������ƍ쓮���܂��B
         *  ��b�ԂŌ��݂̐��l����< value >���オ��܂��B
         *  ���ŃZ�[�u�������I�ɍs���܂��B
         */
        HeartGauge* up( int value );

        /**
         *  �Q�[�W�̗ʂ𑝂₵�܂��B
         *  < value >�Ɏ��R��������ƍ쓮���܂��B
         *  ��b�ԂŌ��݂̐��l����< value >��������܂��B
         *  ���ŃZ�[�u�������I�ɍs���܂��B
         */
        HeartGauge* down( int value );

        /**
         *  �X�N���v�g�p�̃A�N�V�������J�n���܂��B
         *  �����ō폜���s���܂��B
         *  < str >�ɂ͕�����Ő��l����ł��܂��B
         *  < str="10" >�̂悤�Ɏg���܂��B
         */
        HeartGauge* scriptUpAction( std::string const& str );

        /**
         *  �X�N���v�g�p�̃A�N�V�������J�n���܂��B
         *  �����ō폜���s���܂��B
         *  < str >�ɂ͕�����Ő��l����ł��܂��B
         *  < str="10" >�̂悤�Ɏg���܂��B
         */
        HeartGauge* scriptDownAction( std::string const& str );
    private:
        int max = 200;
        int now = 0;
        cocos2d::Size size;
        int start = 0;
        int end = 0;
        int getWidth( int value );
        cocos2d::Sprite* background = nullptr;
    private:
        cocos2d::FiniteTimeAction* createValueAction( int value );
        cocos2d::Sequence* createInValueStopOutExitAction( int value );
    };

    class ScriptHeart : public ScriptBase
    {
    public:
        ScriptHeart( cocos2d::Layer* layer );
    public:
        SCRIPT( up );
        SCRIPT( down );
    };
}

# endif // __ScriptHeart__
