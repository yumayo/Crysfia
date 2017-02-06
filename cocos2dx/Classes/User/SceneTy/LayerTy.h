# ifndef __LayerTy__
# define __LayerTy__

# include "../LayerBase.h"

namespace User
{
    class LayerTy : public LayerBase
    {
    public:
        CREATE_FUNC( LayerTy );
        LayerTy( );
        ~LayerTy( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
    };
}

# endif // __LayerTy__
