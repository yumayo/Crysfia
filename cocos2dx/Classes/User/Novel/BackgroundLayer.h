# ifndef __BackgroundLayer__
# define __BackgroundLayer__

# include "../LayerBase.h"

namespace User
{
    class BackgroundLayer : public LayerBase
    {
    public:
        CREATE_FUNC( BackgroundLayer );
        BackgroundLayer( );
        ~BackgroundLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __BackgroundLayer__
