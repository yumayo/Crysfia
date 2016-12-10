# ifndef __LayerManager__
# define __LayerManager__

# include "cocos2d.h"
#include "../LayerBase.h"

namespace User
{
    class LayerManager : public LayerBase
    {
    public:
		CREATE_FUNC(LayerManager);
        LayerManager( );
        ~LayerManager( );

    private:
		bool init();
    };
}

# endif // __LayerManager__