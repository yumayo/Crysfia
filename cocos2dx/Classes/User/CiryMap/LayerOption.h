# ifndef __LayerOption__
# define __LayerOption__

# include "../LayerBase.h"

#include "ui/CocosGUI.h"

#include "SlideBar.h"

namespace User
{
    /**
     * モーダルレイヤーになっているので、そのままcreateするだけで大丈夫です。
     */
    class LayerOption : public LayerBase
    {
    public:
        LayerOption(){}
        virtual ~LayerOption(){}
        CREATE_FUNC( LayerOption );
        bool init( ) override;
        void setup( ) override;
    private:
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createDeleteButton( );
        cocos2d::Node* createModal( );
        cocos2d::ui::Layout* createDialog( std::string const& str, std::function<void( )>const& yes, std::function<void( )>const& no );
        cocos2d::ui::Button* createSaveMenuButton( );
    };
}

# endif // __LayerOption__
