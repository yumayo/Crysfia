# ifndef __NameLayer__
# define __NameLayer__

# include "../LayerBase.h"

namespace User
{
    class NameLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NameLayer );
        NameLayer( );
        ~NameLayer( );
        bool init( ) override;
        void setup( ) override;
    public:
    };
}

# endif // __NameLayer__
