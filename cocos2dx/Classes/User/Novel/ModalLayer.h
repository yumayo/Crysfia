# ifndef __ModalLayer__
# define __ModalLayer__

# include "cocos2d.h"

# include "../LayerBase.h"

namespace User
{
    class ModalLayer : public LayerBase
    {
    public:
        CREATE_FUNC( ModalLayer );
        virtual bool init( );
    };
}

# endif // __ModalLayer__