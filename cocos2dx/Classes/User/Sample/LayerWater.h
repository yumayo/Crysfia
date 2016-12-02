# ifndef __LayerWater__
# define __LayerWater__

# include "../LayerBase.h"

namespace User
{
    class LayerWater : public LayerBase
    {
    public:
        CREATE_FUNC( LayerWater );
        LayerWater( );
        ~LayerWater( );
        bool init( ) override;
        void setup( ) override;
    public:
        int a = 256;
    };
}

# endif // __LayerWater__
