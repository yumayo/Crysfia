# ifndef __LayerDiary__
# define __LayerDiary__

#include "../LayerBase.h"
#include "ui/CocosGUI.h"

namespace User
{
class LayerDiary : public LayerBase
{
public:
    CREATE_FUNC( LayerDiary );
    bool init( )override;
};
}

# endif // __LayerDiary__
