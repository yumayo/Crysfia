# ifndef __ScriptHeart__
# define __ScriptHeart__

# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "ScriptBase.h"

# include "INIReader.h"

namespace User
{
    class HeartGauge : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( HeartGauge );
        HeartGauge* make( int now );
        void up( int value );
        void down( int value );
    private:
        int max = 200;
        int now = 0;
        cocos2d::Size size;
        int start = 0;
        int end = 0;
        int getWidth( int value );
        cocos2d::Sprite* background = nullptr;

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
        SCRIPT( draw );
    private:

    };
}

# endif // __ScriptHeart__
