# ifndef __HumanLayer__
# define __HumanLayer__

# include "../LayerBase.h"

namespace User
{
    class HumanLayer : public LayerBase
    {
    public:
        CREATE_FUNC( HumanLayer );
        HumanLayer( );
        ~HumanLayer( );
        bool init( ) override;
        void setup( ) override;
    public:
    };
}

# endif // __HumanLayer__
