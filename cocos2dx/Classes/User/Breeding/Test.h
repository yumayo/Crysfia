# ifndef __Test__
# define __Test__

# include "cocos2d.h"

namespace User
{
    class Test : public cocos2d::Layer
    {
    public:
        Test( );
        ~Test( );

		bool init();

		CREATE_FUNC(Test);
	private:

    };
}

# endif // __Test__
