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
         *  滞在中の島
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
         *  今の時間。
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
