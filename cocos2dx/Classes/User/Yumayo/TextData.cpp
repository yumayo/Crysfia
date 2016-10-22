#include "TextData.h"

#include "cocos2d.h"

#include "TextScriptReader.h"

USING_NS_CC;

namespace User
{
    void spaceErase( std::string & lineString )
    {
        // 全角と半角の文字を探す。
        const std::string spaceString = u8" ";
        for ( size_t eraseStr = lineString.find_first_of( spaceString ); eraseStr != std::string::npos; eraseStr = lineString.find_first_of( spaceString ) )
        {
            lineString.erase( eraseStr, spaceString.size( ) );
        }
    }

    void commentErase( std::string & lineString )
    {
        size_t findPosition;
        if ( ( findPosition = lineString.find( u8"//" ) ) != std::string::npos ) lineString = lineString.substr( 0, findPosition );
    }

    void alignFirst( std::string & lineString )
    {
        // 行の先頭に空白があった場合は詰めます。
        size_t findPosition;
        if ( ( findPosition = lineString.find_first_not_of( u8" " ) ) != std::string::npos ) lineString = lineString.substr( findPosition );
    }

    TextData::TextData( )
    {

    }
    TextData::~TextData( )
    {

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
    bool TextData::isEmpty( )
    {
        return data.empty( );
    }
    void TextData::makeData( std::string filePath )
    {
        data.clear( );

        auto fileUtils = FileUtils::getInstance( );
        auto str = fileUtils->getStringFromFile( fileUtils->fullPathForFilename( "data/" + filePath ) );

        size_t stringPosition = 0;
        size_t findPosition = 0;
        const std::string eolString = u8"\r\n";
        const size_t eolSize = std::string( eolString ).size( );
        while ( findPosition != std::string::npos )
        {
            findPosition = str.find( eolString, stringPosition );
            tidydiness( str.substr( stringPosition, findPosition - stringPosition ) );
            stringPosition = findPosition + eolSize;
        }

        for ( auto& line : data )
        {
            log( "%s", line.c_str( ) );
        }
    }
    void TextData::tidydiness( std::string lineString )
    {
        auto commentErased = lineString;
        commentErase( commentErased );
        alignFirst( commentErased );

        auto scriptPosition = commentErased.find( u8"@", 0 );
        // ノベルデータとスクリプトデータが混在している場合
        if ( scriptPosition != std::string::npos )
        {
            auto novelString = commentErased.substr( 0, scriptPosition );
            auto scriptString = commentErased.substr( scriptPosition );
            if ( novelString != u8"" ) data.emplace_back( novelString );
            data.emplace_back( scriptString );
        }
        // ノベルデータだけの場合
        else if ( commentErased != u8"" )
        {
            data.emplace_back( commentErased );
        }
    }
}