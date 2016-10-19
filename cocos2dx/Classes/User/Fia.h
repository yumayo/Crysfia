# ifndef __Fia__
# define __Fia__

# include "Layerbase.h"

namespace User
{
    class Fia : public LayerBase
    {
    public:
        CREATE_FUNC( Fia );
        Fia( );
        ~Fia( );
        bool init( ) override;
        void setup( ) override;
    public:
        int a = 128;
    };
}

# endif // __Fia__
