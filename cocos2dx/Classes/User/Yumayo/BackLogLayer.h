# ifndef __BackLogLayer__
# define __BackLogLayer__

# include "../LayerBase.h"

namespace User
{
    class BackLogLayer : public LayerBase
    {
    public:
        CREATE_FUNC( BackLogLayer );
        BackLogLayer( );
        ~BackLogLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __BackLogLayer__
