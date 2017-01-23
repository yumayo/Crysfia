# ifndef __SystemLayer__
# define __SystemLayer__

# include "../LayerBase.h"

namespace User
{
    class SystemLayer : public LayerBase
    {
    public:
        CREATE_FUNC( SystemLayer );
        SystemLayer( );
        ~SystemLayer( );
        bool init( ) override;
        void setup( ) override;
    public:
    };
}

# endif // __SystemLayer__
