# ifndef __NameLayer__
# define __NameLayer__

# include "../LayerBase.h"

namespace User
{
    class NameLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NameLayer );
        NameLayer( );
        ~NameLayer( );
        bool init( ) override;
        void setup( ) override;
    public:
        void addNovelWinodowSwitch( );
    public:
        void on( );
        void off( );
        void novelenable( );
        void noveldisable( );
    };
}

# endif // __NameLayer__
