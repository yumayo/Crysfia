# ifndef __LayerManager__
# define __LayerManager__

# include "cocos2d.h"
#include "../LayerBase.h"
#include "../SceneBase.h"

namespace User
{
    class LayerManager : public LayerBase
    {
    public:
		CREATE_FUNC(LayerManager);
        LayerManager( );
        ~LayerManager( );

	private:
		
		bool init();

	public:

		void initLayer();
		void changeToMainMenuLayer();
		void changeToSubMenuLayer();
		void removeLayer();

    };
}

# endif // __LayerManager__