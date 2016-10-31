# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

namespace User
{
    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        //LayerColor * createBlockLayer( const char *strlabel, Color3B fontColor, Color4B backColor );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    };
}

# endif // __LayerIsland__
