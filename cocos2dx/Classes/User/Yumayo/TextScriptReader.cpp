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
    TagWithNovelStringAndRawScriptPartsData TextScriptReader::createTagRawScriptPartsData( std::string const& lineRawData )
    {
        // 文字列の先頭に"@"がある場合はスクリプト
        if ( lineRawData[0] == '@' )
        {
            // 先頭の"@"の後ろのデータを渡します。
            this->rawLineData = lineRawData.substr( std::string( u8"@" ).size( ) );
            makeTagRawScriptData( );
        }
        // そうでない場合はノベルデータです。
        else
        {
            this->rawLineData = lineRawData;
            makeNovelData( );
        }

        return getCleanedData( );
    }
    void TextScriptReader::makeNovelData( )
    {
        tagWithNovelStringAndRawScriptPartsData = { TagWithNovelStringAndRawScriptPartsData::Tag::NOV, rawLineData, RawScriptPartsData( ) };
    }
    void TextScriptReader::makeTagRawScriptData( )
    {
        auto scriptLine = rawLineData;
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
            if ( str != u8"" ) rawScriptPartsData.emplace_back( str );
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
                rawScriptPartsData.emplace_back( findSyntaxItr->partsString );
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

        syntaxCheck( rawScriptPartsData );

        // 変数名のところに"$"マークがあれば新しい変数として作成出来ます。
        if ( rawScriptPartsData[0].find( u8"$" ) != std::string::npos )
        {
            tagWithNovelStringAndRawScriptPartsData = { TagWithNovelStringAndRawScriptPartsData::Tag::VAR, u8"", rawScriptPartsData };
        }
        // 違うなら、関数呼び出しになります。
        else
        {
            tagWithNovelStringAndRawScriptPartsData = { TagWithNovelStringAndRawScriptPartsData::Tag::FUN, u8"", rawScriptPartsData };
        }
    }
    void TextScriptReader::syntaxCheck( RawScriptPartsData const & rawScriptPartsData )
    {
        auto error = [ ] ( std::string const& errorString ) { throw( "syntaxError : " + errorString ); };
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

        auto& raw = rawScriptPartsData;

        TagWithNovelStringAndRawScriptPartsData::Tag tag;

        if ( raw.size( ) < 3U ) error( "最低限 [@ NAME : RUN] の形で記入してください。" );

        if ( raw[1] != u8":" ) error( "ペア表現に誤りがあります。" );

        if ( raw[0].find( u8"$" ) != std::string::npos ) tag = TagWithNovelStringAndRawScriptPartsData::Tag::VAR;
        else tag = TagWithNovelStringAndRawScriptPartsData::Tag::FUN;

        switch ( tag )
        {
        case User::TagWithNovelStringAndRawScriptPartsData::Tag::VAR:
            do
            {
                if ( 3U < raw.size( ) ) error( "変数の実体は一つでないといけません。" );
                if ( !isValue( raw[2] ) ) error( "変数宣言に対する数字が不正な値です。" );
            } while ( false );
            break;
        case User::TagWithNovelStringAndRawScriptPartsData::Tag::FUN:
            do
            {
                if ( 3U < raw.size( ) )
                {
                    if ( raw[3] != u8"(" ) error( "関数の引数構文が間違っています。" );
                    if ( raw.back( ) != u8")" ) error( "関数の引数リストの最後に \")\" がありません。" );

                    for ( size_t i = 4; i < raw.size( ) - 1; ++i )
                    {
                        if ( ( i & 0x1 ) == 0x1 ) // 奇数
                        {
                            if ( raw[i] != u8"," ) error( "関数の引数リストが正常ではありません。" );
                        }
                        else // 偶数
                        {
                            // 全てがアルファベットであるか、数字として有効ならOKです。
                            if ( !isAllAlphabet( raw[i] ) && !isValue( raw[i] ) )
                            {
                                // 変数でなかったらエラーを飛ばします。
                                if ( raw[i].find( u8"$" ) == std::string::npos ) error( "関数の引数が不正な値です。" );
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
    TagWithNovelStringAndRawScriptPartsData TextScriptReader::getCleanedData( )
    {
        auto script = tagWithNovelStringAndRawScriptPartsData;
        cleanUp( );
        return script;
    }
    void TextScriptReader::cleanUp( )
    {
        rawLineData.clear( );

        rawScriptPartsData.clear( );

        tagWithNovelStringAndRawScriptPartsData.tag = TagWithNovelStringAndRawScriptPartsData::Tag::NIL;
        tagWithNovelStringAndRawScriptPartsData.novel.clear( );
        tagWithNovelStringAndRawScriptPartsData.script.clear( );
    }
}