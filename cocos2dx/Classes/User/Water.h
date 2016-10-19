# ifndef __Water__
# define __Water__

# include "LayerBase.h"

namespace User
{
    class Water : public LayerBase
    {
    public:
        CREATE_FUNC( Water );
        Water( );
        ~Water( );
        bool init( ) override;
        void setup( ) override;
    public:
        int a = 256;
    };
}

# endif // __Water__
