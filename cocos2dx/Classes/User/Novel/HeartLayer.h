# ifndef __HeartLayer__
# define __HeartLayer__

# include "../LayerBase.h"

namespace User
{
    class HeartLayer : public LayerBase
    {
    public:
        CREATE_FUNC( HeartLayer );
        HeartLayer( );
        ~HeartLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __HeartLayer__
