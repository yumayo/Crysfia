# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
        /**
         *  ‘Øİ’†‚Ì“‡
         */
        enum Islands
        {
            none,
            rashasu,
            hyarukisi,
            aikura,
            END,
        };

        /**
         *  ¡‚ÌŠÔB
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
    private:
        Islands islands = Islands::rashasu;
        Times times = Times::morning;
    };
}

# endif // __LayerIsland__
