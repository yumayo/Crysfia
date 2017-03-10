#include "INIReader.h"

#include <fstream>

#include "TextData.h"

#include "cocos2d.h"

USING_NS_CC;

namespace User
{
    INIReader::INIReader( )
    {

    }

    INIReader::INIReader( const std::string & filePath )
    {
        read( filePath );
    }

    void INIReader::read( const std::string & filePath )
    {
        auto fileUtils = FileUtils::getInstance( );
        auto fullPath = fileUtils->fullPathForFilename( filePath );
        auto str = fileUtils->getStringFromFile( fullPath );

        size_t stringPosition = 0;
        size_t findPosition = 0;
        const std::string eolString = u8"\n";
        const size_t eolSize = std::string( eolString ).size( );

        std::string lineStr;
        std::string fieldBuffer;

        while ( findPosition != std::string::npos )
        {
            findPosition = str.find( eolString, stringPosition );
            lineStr = str.substr( stringPosition, findPosition - stringPosition );

            lineStr = this->commentErase( spaceErase( lineStr ) );
            User::commentErase( lineStr );
            if ( !lineStr.empty( ) )
            {
                if ( findLineField( lineStr ) )
                {
                    fieldBuffer = fieldName( lineStr );
                }
                else
                {
                    if ( !fieldBuffer.empty( ) )
                    {
                        if ( findValue( lineStr ) )
                        {
                            auto insert = fieldValue( lineStr );
                            data[fieldBuffer][insert.first] = insert.second;
                        }
                    }
                }
            }

            stringPosition = findPosition + eolSize;
        }
    }

    std::map<std::string, std::string>& INIReader::findField( const std::string & field )
    {
        return data[field];
    }

    std::string INIReader::spaceErase( std::string lineStr )
    {
        for ( size_t eraseStr = lineStr.find_first_of( ' ' ); eraseStr != std::string::npos; eraseStr = lineStr.find_first_of( ' ' ) )
        {
            lineStr.erase( eraseStr, 1 );
        }
        return lineStr;
    }

    std::string INIReader::commentErase( std::string lineStr )
    {
        size_t beginComment;
        if ( ( beginComment = lineStr.find( ';' ) ) != std::string::npos )
        {
            return lineStr.substr( 0, beginComment );
        }
        return lineStr;
    }

    bool INIReader::findLineField( std::string lineStr )
    {
        return lineStr.find( '[' ) != std::string::npos && lineStr.find( ']' ) != std::string::npos;
    }

    bool INIReader::findValue( std::string lineStr )
    {
        lineStr = lineStr.substr( lineStr.find( '=' ) + 1 );

        if ( lineStr.find( '=' ) == std::string::npos ) return true;
        else return false;
    }

    std::string INIReader::fieldName( std::string lineStr )
    {
        size_t beginField = lineStr.find( '[' );
        size_t endField = lineStr.find( ']' );
        size_t fieldNum = endField - beginField;
        return lineStr.substr( beginField + 1, fieldNum - 1 );
    }

    std::pair<std::string, std::string> INIReader::fieldValue( std::string lineStr )
    {
        size_t equal = lineStr.find( '=' );

        std::string first, second;
        first = lineStr.substr( 0, equal );
        second = lineStr.substr( equal + 1 );

        return std::pair<std::string, std::string>( first, second );
    }
}