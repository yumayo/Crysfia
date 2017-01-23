# ifndef __SaveLayer__
# define __SaveLayer__

# include "../LayerBase.h"

namespace User
{
    class SaveLayer : public LayerBase
    {
    public:
        CREATE_FUNC( SaveLayer );
        SaveLayer( );
        ~SaveLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __SaveLayer__
