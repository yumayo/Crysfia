# ifndef __StillLayer__
# define __StillLayer__

# include "../LayerBase.h"

namespace User
{
    class StillLayer : public LayerBase
    {
    public:
        CREATE_FUNC( StillLayer );
        StillLayer( );
        ~StillLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __StillLayer__
