#include "TextScriptReader.h"

#include "TextData.h"

#include <functional>
#include <algorithm>

namespace User
{
    TextScriptReader::TextScriptReader( )
    {

    }
    TextScriptReader::~TextScriptReader( )
    {

    }
    TagWithData TextScriptReader::createTagRawScriptPartsData( DebugWithLineData const& debugWithLineData )
    {
        // 文字列の先頭に"@"がある場合はスクリプト
        if ( debugWithLineData.lineData[0] == '@' )
        {
            // 先頭の"@"の後ろのデータを渡します。
            this->lineData = debugWithLineData.lineData.substr( std::string( u8"@" ).size( ) );
            this->debugData = debugWithLineData.debugData;
            makeTagRawScriptData( );
        }
        // そうでない場合はノベルデータです。
        else
        {
            this->lineData = debugWithLineData.lineData;
            this->debugData = debugWithLineData.debugData;
            makeNovelData( );
        }

        return getCleanedData( );
    }
    void TextScriptReader::makeNovelData( )
    {
        tagWithData = { TagWithData::Tag::NOV, debugData, StringArray( ), lineData };
    }
    void TextScriptReader::makeTagRawScriptData( )
    {
        scriptParts.clear( );

        auto scriptLine = lineData;
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
            tagWithData = { TagWithData::Tag::VAR, debugData, scriptParts, u8"" };
        }
        // 違うなら、関数呼び出しになります。
        else
        {
            tagWithData = { TagWithData::Tag::FUN, debugData, scriptParts, u8"" };
        }
    }
    void TextScriptReader::syntaxCheck( StringArray const & scriptParts )
    {
        auto error = [ &, this ] ( std::string const& errorString ) { throw( "[syntaxError : " + errorString + "][ file : " + debugData.fileName + "][line : " + std::to_string( debugData.lineNumber ) + "]" ); };
        auto isAllAlphabet = [ & ] ( std::string const& string )
        {
            return std::all_of( string.cbegin( ), string.cend( ), isalpha );
        };
        auto isValue = [ & ] ( std::string const& string )
        {
            double value;
            try { value = std::stod( string ); }
            catch ( const std::logic_error& e ) { return false; }
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
            do
            {
                if ( 3U < parts.size( ) ) error( "変数の実体は一つでないといけません。" );
                if ( !isValue( parts[2] ) ) error( "変数宣言に対する数字が不正な値です。" );
            } while ( false );
            break;
        case User::TagWithData::Tag::FUN:
            do
            {
                if ( 3U < parts.size( ) )
                {
                    if ( parts[3] != u8"(" ) error( "関数の引数構文が間違っています。" );
                    if ( parts.back( ) != u8")" ) error( "関数の引数リストの最後に \")\" がありません。" );

                    for ( size_t i = 4; i < parts.size( ) - 1; ++i )
                    {
                        if ( ( i & 0x1 ) == 0x1 ) // 奇数
                        {
                            if ( parts[i] != u8"," ) error( "関数の引数リストが正常ではありません。" );
                        }
                        else // 偶数
                        {
                            // 全てがアルファベットであるか、数字として有効ならOKです。
                            if ( !isAllAlphabet( parts[i] ) && !isValue( parts[i] ) )
                            {
                                // 変数でなかったらエラーを飛ばします。
                                if ( parts[i].find( u8"$" ) == std::string::npos ) error( "関数の引数が不正な値です。" );
                            }
                        }
                    }
                }
            } while ( false );
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
        lineData.clear( );

        debugData.fileName.clear( );
        debugData.lineNumber = 0;

        tagWithData.tag = TagWithData::Tag::NIL;
        tagWithData.debugData.fileName.clear( );
        tagWithData.debugData.lineNumber = 0;
        tagWithData.novel.clear( );
        tagWithData.scriptParts.clear( );
    }
}