# ifndef __TextLabels__
# define __TextLabels__

# include "cocos2d.h"

# include "TextTypes.hpp"
# include "TextString.h"

namespace User
{
    class TextLabels
    {
    public:
        TextLabels( cocos2d::Layer* layer );
        ~TextLabels( );
    public:
        void clear( );
        void setStrings( NovelData const& strings, cocos2d::Vec2 position );

        void actionStop( );
        bool getIsReadOuted( );
        std::function<void( )> animationEndCallBack;
    private:
        cocos2d::Layer* layer;
        std::array<TextString, lineSize> textStrings;
        bool isReadOuted = false;
    };
}

# endif // __TextLabels__
