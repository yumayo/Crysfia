# ifndef __TextLabels__
# define __TextLabels__

# include "TextTypes.hpp"
# include "TextString.h"

namespace User
{
    class TextLabels
    {
    public:
        TextLabels( );
        ~TextLabels( );
    public:
        void clear( );
        void setStrings( NovelData const& strings, cocos2d::Vec2 position );
        // レイヤーに貼り付け
        void layerPasting( cocos2d::Layer* layer );
        // レイヤーから剥がす
        void layerPeelOff( cocos2d::Layer* layer );

        void actionStop( );
        bool getIsReadOuted( );
    private:
        void line1CallBack( );
        void line2CallBack( );
        void line3CallBack( );
    private:
        std::array<TextString, lineSize> textStrings;
        bool isReadOuted = false;
    };
}

# endif // __TextLabels__
