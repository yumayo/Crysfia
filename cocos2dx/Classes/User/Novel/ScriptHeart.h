# ifndef __ScriptHeart__
# define __ScriptHeart__

# include "cocos2d.h"

# include "ScriptBase.h"

# include "INIReader.h"

namespace User
{
    class ScriptHeart : public ScriptBase
    {
    public:
        ScriptHeart( cocos2d::Layer* layer, std::string const& filePath );
        ~ScriptHeart( );
    public:
        SCRIPT( up );
        SCRIPT( down );
    private:
        void favorabilityRating( int value );
    private:
        INIReader reader;
        std::string filePath;
    };
}

# endif // __ScriptHeart__
