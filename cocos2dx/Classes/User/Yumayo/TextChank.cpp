#include "TextChank.h"

#include "ScriptStaticData.h"
#include "ScriptSystem.h"

#include <algorithm>

namespace User
{
    TextChank::TextChank( )
        : novelIndex( ScriptSystem::novelIndex )
    {

    }
    TextChank::~TextChank( )
    {

    }
    void TextChank::insertScript( TagWithNovelStringAndRawScriptPartsData const & tagWithNovelStringAndRawScriptPartsData )
    {
        bufferTagWithNovelStringAndRawScriptPartsData = tagWithNovelStringAndRawScriptPartsData;
        switch ( bufferTagWithNovelStringAndRawScriptPartsData.tag )
        {
        case TagWithNovelStringAndRawScriptPartsData::Tag::NOV:
            makeNovel( );
            break;
        case TagWithNovelStringAndRawScriptPartsData::Tag::VAR:
            makeVariableScript( );
            break;
        case TagWithNovelStringAndRawScriptPartsData::Tag::FUN:
            makeFunctionScript( );
            callFunction( );
            break;
        default:
            return;
            break;
        }
    }
    bool TextChank::isNext( )
    {
        return novelIndex == novelData.size( );
    }
    NovelData TextChank::getNovelData( )
    {
        return novelData;
    }
    void TextChank::clear( )
    {
        bufferTagWithNovelStringAndRawScriptPartsData.tag = TagWithNovelStringAndRawScriptPartsData::Tag::NIL;
        bufferTagWithNovelStringAndRawScriptPartsData.novel.clear( );
        bufferTagWithNovelStringAndRawScriptPartsData.script.clear( );

        functionScriptChip.variable.clear( );
        functionScriptChip.functionInfo.name.clear( );
        functionScriptChip.functionInfo.argumentList.clear( );

        functionScriptData.clear( );

        //variableScriptData.clear( ); // 変数の初期化はしない。

        novelIndex = 0;

        for ( auto& obj : novelData ) obj = u8"";
    }
    void TextChank::makeVariableScript( )
    {
        auto data = bufferTagWithNovelStringAndRawScriptPartsData.script;

        auto values = data;
        auto variableName = data[0]; // 生データの 配列0番目には、変数名が記載されています。
        auto currentStatusName = data[2]; // 生データの 配列2番目には、その変数の実体が記載されています。

        variableScriptData.insert( std::make_pair( variableName, currentStatusName ) );
    }
    void TextChank::makeFunctionScript( )
    {
        auto data = bufferTagWithNovelStringAndRawScriptPartsData.script;

        auto values = data;
        auto variableName = data[0]; // 生データの 配列0番目には、変数名が記載されています。
        auto functionName = data[2]; // 生データの 配列2番目には、関数名が記載されています。

        // 引数なしの場合
        // 文法上関数の"()"を省略できるようにしているので。
        if ( values.size( ) == 3U )
        {
            // 関数情報を作成。
            // 関数の名前と、引数リストを保存します。
            FunctionInfo functionInfo = { functionName, ArgumentList( ) };

            // 最終的に、関数情報を持ったマップを生成します。
            functionScriptChip = { variableName, functionInfo };
            functionScriptData.insert( std::make_pair( functionScriptChip.variable, functionScriptChip.functionInfo ) );
        }
        // 引数ありの場合
        // "()"を明示的に書いてもOKなようにしています。
        else
        {
            auto error = [ ] ( std::string const& errorString ) { throw( "variableError : " + errorString ); };

            // 関数の引数だけを残します。
            values.erase( values.begin( ), values.begin( ) + 4 );
            values.pop_back( );

            // 引数リストを作成します。
            ArgumentList argumentList;
            // 2つ飛ばしなのは、間に","があるため。
            // ほんとうに必要なのは、偶数番にある引数のみです。
            for ( size_t i = 0; i < values.size( ); i += 2 )
            {
                if ( values[i].find( u8"$" ) != std::string::npos )
                {
                    auto itr = variableScriptData.find( values[i] );
                    if ( itr != variableScriptData.cend( ) ) argumentList.emplace_back( itr->second );
                    else error( "指定した変数が存在しません。" );
                }
                else argumentList.emplace_back( values[i] );

            }
            // 関数情報を作成。
            // 関数の名前と、引数リストを保存します。
            FunctionInfo functionInfo = { functionName, argumentList };

            // 最終的に、関数情報を持ったマップを生成します。
            functionScriptChip = { variableName, functionInfo };
            functionScriptData.insert( std::make_pair( functionScriptChip.variable, functionScriptChip.functionInfo ) );
        }
    }
    void TextChank::makeNovel( )
    {
        novelIndex = std::min( novelIndex + 1U, novelData.size( ) );

        novelData[novelIndex - 1] = bufferTagWithNovelStringAndRawScriptPartsData.novel;
    }
    void TextChank::callFunction( )
    {
        ScriptStaticData::run( functionScriptChip );
    }
}
