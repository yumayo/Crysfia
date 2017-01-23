#include "INIWriter.h"

#include <fstream>
#include <sstream>

#include "cocos2d.h"

USING_NS_CC;

namespace User
{
    void INIWriter::write( const std::string & filePath, INIReader const & reader )
    {
        write( filePath, reader.data );
    }
    void INIWriter::write( const std::string & filePath, std::map<std::string, std::map<std::string, std::string>> const & data )
    {
        std::stringstream output;
        std::map<std::string, std::map<std::string, std::string>>::const_iterator fieldItr;
        for ( fieldItr = data.cbegin( ); fieldItr != data.cend( ); fieldItr++ )
        {
            output << fieldWrite( fieldItr->first ) << std::endl;

            std::map<std::string, std::string>::const_iterator valueItr;
            for ( valueItr = fieldItr->second.cbegin( ); valueItr != fieldItr->second.cend( ); valueItr++ )
            {
                if ( grammarValueCheck( *valueItr ) )
                {
                    output << valuesWrite( std::pair<std::string, std::string>( valueItr->first, valueItr->second ) ) << std::endl;
                }
            }
        }

        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeStringToFile( output.str( ), path + filePath );
        }
    }

    std::string INIWriter::fieldWrite( const std::string & field )
    {
        return '[' + field + "]";
    }

    bool INIWriter::grammarValueCheck( const std::pair<std::string, std::string>& value )
    {
        return value.first != "" && value.second != "";
    }

    std::string INIWriter::valuesWrite( const std::pair<std::string, std::string>& values )
    {
        return values.first + " = " + values.second;
    }
}
