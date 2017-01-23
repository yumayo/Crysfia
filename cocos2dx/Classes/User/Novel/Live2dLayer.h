# ifndef __Live2dLayer__
# define __Live2dLayer__

# include "../LayerBase.h"

namespace User
{
    class Live2dLayer : public LayerBase
    {
    public:
        CREATE_FUNC( Live2dLayer );
        Live2dLayer( );
        ~Live2dLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __Live2dLayer__
