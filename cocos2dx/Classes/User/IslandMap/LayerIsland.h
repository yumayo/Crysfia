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
        cocos2d::Label* LayerIsland::createLabel( std::string const& text );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        bool initBackground( );
        bool initIslandMap( );
    };
}

# endif // __LayerIsland__
