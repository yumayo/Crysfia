# ifndef __DataSettings__
# define __DataSettings__

# include "cocos2d.h"

# include "../Novel/INIReader.h"

#include "json/rapidjson.h"
#include "json/document.h"

namespace User
{
    void iniDataRead( INIReader& reader, std::string const& name );
    void iniDataRead( INIReader& reader, std::string const& name, std::string const& defalutDirectory );
    void setUserDefault( INIReader& iniReader );
    INIReader getUserDefault( INIReader& iniReader );
    void userDefaultSetup( );
    void userDefaultForceSetup( );
    std::string getLocalReadPath( std::string const& name );
    std::string getLocalReadPath( std::string const& name, std::string const& directory );
    void writeUserLocal( std::string const& data, std::string const& name );
    void writeUserLocal( std::string const& data, std::string const& name, std::string const& directory );
    void writeDataUserLocal( cocos2d::Data const& data, std::string const& name );
    void writeDataUserLocal( cocos2d::Data const& data, std::string const& name, std::string const& directory );
    void restart( );
    std::string getDiary( int const& day );
}

# endif // __DataSettings__