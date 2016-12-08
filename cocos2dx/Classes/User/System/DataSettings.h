# ifndef __DataSettings__
# define __DataSettings__

# include "cocos2d.h"

# include "../Novel/INIReader.h"

namespace User
{
    void iniDataRead( INIReader& reader, std::string const& name );
    void iniDataRead( INIReader& reader, std::string const& name, std::string const& defalutDirectory );
    void userDefaultLoading( );
    void userDefaultSaveing( );
    void userDefaultSetup( );

}

# endif // __DataSettings__