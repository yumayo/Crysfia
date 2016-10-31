# ifndef __Test__
# define __Test__

# include "cocos2d.h"
#include "ui/CocosGUI.h" 
namespace User
{
    class Test : public cocos2d::ui::Button
    {
    public:
        Test( );
		~Test() {}
		bool init();

		CREATE_FUNC(Test);
    private:

    };
}

# endif // __Test__
