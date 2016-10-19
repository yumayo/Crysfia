#include "TextData.h"

#include "cocos2d.h"
USING_NS_CC;

namespace User
{
    TextData::TextData( )
    {
        auto fileUtils = FileUtils::getInstance( );
        auto str = fileUtils->getStringFromFile( fileUtils->fullPathForFilename( "data/script.txt" ) );

        size_t stringPosition = 0;
        size_t findPosition = 0;
        const std::string eolString = u8"\r\n";
        const size_t eolSize = std::string( eolString ).size( );
        while ( findPosition != std::string::npos )
        {
            findPosition = str.find( eolString, stringPosition );
            data.emplace_back( str.substr( stringPosition, findPosition - stringPosition ) );
            stringPosition = findPosition + eolSize;
        }
        CCLOG( "%s", str.c_str( ) );
    }
    TextData::~TextData( )
    {

    }
    NovelData TextData::getNovelDataMoved( )
    {
        NovelData strings;

        auto getString = [ this ]
        {
            std::string temp;
            if ( data.empty( ) )
            {
                temp = u8"";
            }
            else
            {
                temp = data[0];
                data.pop_front( );
            }
            return temp;
        };

        for ( auto& obj : strings ) obj = getString( );

        return strings;
    }
    std::string TextData::getLineMoved( )
    {
        std::string temp;
        if ( data.empty( ) )
        {
            temp = u8"";
        }
        else
        {
            temp = data[0];
            data.pop_front( );
        }
        return temp;
    }
}