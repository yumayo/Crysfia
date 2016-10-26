#include "TextScriptReader.h"

#include "TextData.h"

#include <functional>
#include <algorithm>

namespace User
{
    TagWithData TextScriptReader::createTagWithData( DebugWithLineData const& debugWithLineData )
    {
        this->debugWithLineData = debugWithLineData;

        // 文字列の先頭に"@"がある場合はスクリプト
        if ( debugWithLineData.lineData[0] == '@' ) makeScriptData( );
        // そうでない場合はノベルデータです。
        else makeNovelData( );

        return getCleanedData( );
    }
    void TextScriptReader::makeNovelData( )
    {
        tagWithData = { TagWithData::Tag::NOV, debugWithLineData.debugData, StringArray( ), debugWithLineData.lineData };
    }
    void TextScriptReader::makeScriptData( )
    {
        StringArray scriptParts;

        auto scriptLine = debugWithLineData.lineData.substr( std::string( u8"@" ).size( ) );
        spaceErase( scriptLine );

        size_t findPosition = 0;
        std::string findString;

        auto find = [ & ] ( std::string const& $findString )
        {
            findString = $findString;
            return ( findPosition = scriptLine.find_first_of( $findString ) ) != std::string::npos;
        };

        auto partsAdd = [ & ] ( size_t findPosition )
        {
            auto str = scriptLine.substr( 0, findPosition );
            if ( str != u8"" ) scriptParts.emplace_back( str );
        };

        struct Syntax
        {
            bool isFind;
            std::string partsString;
            size_t position;
        };

        std::function<void( )> disassembly = [ & ]
        {
            std::vector<Syntax> syntaxs;
            syntaxs.push_back( { find( u8":" ), findString, findPosition } );
            syntaxs.push_back( { find( u8"(" ), findString, findPosition } );
            syntaxs.push_back( { find( u8")" ), findString, findPosition } );
            syntaxs.push_back( { find( u8"," ), findString, findPosition } );

            auto findSyntaxItr = std::min_element( syntaxs.begin( ), syntaxs.end( ), [ ] ( Syntax& a, Syntax& b )
            {
                return a.position < b.position;
            } );

            // 構文が見つかった場合は、どんどん分割していきます。
            if ( findSyntaxItr->isFind )
            {
                partsAdd( findSyntaxItr->position );
                scriptParts.emplace_back( findSyntaxItr->partsString );
                scriptLine = scriptLine.substr( findSyntaxItr->position + std::string( findSyntaxItr->partsString ).size( ) );

                disassembly( );
            }
            // 構文が見つからなかった場合は、残った文字を追加して終了です。
            else
            {
                partsAdd( findSyntaxItr->position );
            }
        };

        disassembly( );

        syntaxCheck( scriptParts );

        // 変数名のところに"$"マークがあれば新しい変数として作成出来ます。
        if ( scriptParts[0].find( u8"$" ) != std::string::npos )
        {
            tagWithData = { TagWithData::Tag::VAR, debugWithLineData.debugData, scriptParts, u8"" };
        }
        // 違うなら、関数呼び出しになります。
        else
        {
            tagWithData = { TagWithData::Tag::FUN, debugWithLineData.debugData, scriptParts, u8"" };
        }
    }
    void TextScriptReader::syntaxCheck( StringArray const & scriptParts )
    {
        auto error = [ &, this ] ( std::string const& errorString ) 
        { 
            std::string str;
            str += "[syntaxError : " + errorString + "]";
            str += "[file:" + debugWithLineData.debugData.fileName + "]";
            str += "[line : " + std::to_string( debugWithLineData.debugData.lineNumber ) + "]";
            throw( str );
        };
        auto isAllAlphabet = [ & ] ( std::string const& string )
        {
            return std::all_of( string.cbegin( ), string.cend( ), isalpha );
        };
        auto isValue = [ & ] ( std::string const& string )
        {
            double value;
            try { value = std::stod( string ); }
            catch ( ... ) { return false; }
            return true;
        };

        auto& parts = scriptParts;

        TagWithData::Tag tag;

        if ( parts.size( ) < 3U ) error( "最低限 [@ NAME : RUN] の形で記入してください。" );

        if ( parts[1] != u8":" ) error( "ペア表現に誤りがあります。" );

        if ( parts[0].find( u8"$" ) != std::string::npos ) tag = TagWithData::Tag::VAR;
        else tag = TagWithData::Tag::FUN;

        switch ( tag )
        {
        case User::TagWithData::Tag::VAR:
            if ( 3U != parts.size( ) ) error( "変数の実体は一つでないといけません。" );
            if ( !isValue( parts[2] ) ) error( "変数宣言に対する数字が不正な値です。" );
            break;
        case User::TagWithData::Tag::FUN:
            if ( 3U < parts.size( ) )
            {
                if ( parts[3] != u8"(" ) error( "関数の引数構文が間違っています。" );
                if ( parts.back( ) != u8")" ) error( "関数の引数リストの最後に \")\" がありません。" );

                for ( size_t i = 5; i < parts.size( ) - 1; i += 2 )
                {
                    if ( parts[i] != u8"," ) error( "関数の引数リストが正常ではありません。" );
                }
            }
            break;
        default:
            break;
        }
    }
    TagWithData TextScriptReader::getCleanedData( )
    {
        auto script = tagWithData;
        cleanUp( );
        return script;
    }
    void TextScriptReader::cleanUp( )
    {
        debugWithLineData.lineData.clear( );
        debugWithLineData.debugData.fileName.clear( );
        debugWithLineData.debugData.lineNumber = 0;

        tagWithData.tag = TagWithData::Tag::NIL;
        tagWithData.debugData.fileName.clear( );
        tagWithData.debugData.lineNumber = 0;
        tagWithData.novel.clear( );
        tagWithData.scriptParts.clear( );
    }
}