# ifndef __LayerSave__
# define __LayerSave__

# include "../LayerBase.h"

#include "ui/CocosGUI.h"

namespace User
{
    /**
     * モーダルレイヤーになっているので、そのままcreateするだけで大丈夫です。
     */
    class LayerSave : public LayerBase
    {
    public:
        CREATE_FUNC( LayerSave );
        LayerSave( );
        ~LayerSave( );
        bool init( ) override;
        void setup( ) override;
    private:
        cocos2d::ui::Button* createBackButton( );
        cocos2d::Node* createModal( );
        cocos2d::ui::Layout* createDialog( std::string const& str, std::function<void( )> const & yes, std::function<void( )> const & no );
        cocos2d::ui::Layout* createSavePanel( std::string const& name );
        cocos2d::ui::Layout* createSavePanelSide( std::string const& left_name, std::string const& right_name );
        cocos2d::Size panelSize; // セーブデータパネルの大きさを格納します。
    };
}

# endif // __LayerSave__
