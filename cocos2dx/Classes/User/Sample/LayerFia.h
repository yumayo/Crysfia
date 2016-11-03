# ifndef __LayerFia__
# define __LayerFia__

# include "../Layerbase.h"

namespace User
{
    class LayerFia : public LayerBase
    {
    public:
        CREATE_FUNC( LayerFia );
        LayerFia( );
        ~LayerFia( );
        bool init( ) override;
        void setup( ) override;
    public:
        int a = 128;
    };
}

# endif // __LayerFia__
