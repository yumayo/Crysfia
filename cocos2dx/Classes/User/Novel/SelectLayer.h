# ifndef __SelectLayer__
# define __SelectLayer__

# include "../LayerBase.h"

namespace User
{
    class SelectLayer : public LayerBase
    {
    public:
        CREATE_FUNC( SelectLayer );
        SelectLayer( );
        ~SelectLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __SelectLayer__
