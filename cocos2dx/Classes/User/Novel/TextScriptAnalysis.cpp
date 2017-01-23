#include "TextScriptAnalysis.h"

#include "ScriptStaticData.h"
#include "ScriptSystem.h"

#include <algorithm>

namespace User
{
    void TextScriptAnalysis::makeScript( TagWithData const& tagWithData )
    {
        this->tagWithData = tagWithData;
        switch ( tagWithData.tag )
        {
        case TagWithData::Tag::NOV:
            makeNovelScript( );
            break;
        case TagWithData::Tag::VAR:
            makeVariableScript( );
            break;
        case TagWithData::Tag::FUN:
            makeFunctionScript( );
            break;
        default:
            return;
            break;
        }
    }
    void TextScriptAnalysis::clear( )
    {
        tagWithData.tag = TagWithData::Tag::NIL;
        tagWithData.debugData.fileName.clear( );
        tagWithData.debugData.lineNumber = 0;
        tagWithData.novel.clear( );
        tagWithData.scriptParts.clear( );

        functionScript.variable.clear( );
        functionScript.functionInfo.name.clear( );
        functionScript.functionInfo.argumentList.clear( );

        variableScript.variable.clear( );
        variableScript.currentStatus.clear( );

        novelScript.novel.clear( );
    }
    void TextScriptAnalysis::makeVariableScript( )
    {
        auto variableName = tagWithData.scriptParts[0]; // 生データの 配列0番目には、変数名が記載されています。
        auto currentStatusName = tagWithData.scriptParts[2]; // 生データの 配列2番目には、その変数の実体が記載されています。

        variableScript = { variableName, currentStatusName };
    }
    void TextScriptAnalysis::makeFunctionScript( )
    {
        auto variableName = tagWithData.scriptParts[0]; // 生データの 配列0番目には、変数名が記載されています。
        auto functionName = tagWithData.scriptParts[2]; // 生データの 配列2番目には、関数名が記載されています。

        // 引数なしの場合
        // 文法上関数の引数がない場合は"()"を省略できるようにしているので。
        if ( tagWithData.scriptParts.size( ) == 3U )
        {
            // 関数情報を作成。
            // 関数の名前と、引数リストを保存します。
            FunctionInfo functionInfo = { functionName, ArgumentList( ) };

            functionScript = { variableName, functionInfo };
        }
        // 引数ありの場合
        // "()"を明示的に書いてもOKなようにしています。
        else
        {
            // 関数の引数だけを残します。
            auto values = tagWithData.scriptParts; // [var][:][name][(][hoge][,][huga]...[)]
            values.erase( values.begin( ), values.begin( ) + 4 ); // [hoge][,][huga]...[)]
            values.pop_back( ); // [hoge][,][huga]...

            // 引数リストを作成します。
            ArgumentList argumentList;
            // 2つ飛ばしなのは、間に","があるため。
            // ほんとうに必要なのは、偶数番にある引数のみです。
            for ( size_t i = 0; i < values.size( ); i += 2 ) argumentList.emplace_back( values[i] );
            // 関数情報を作成。
            // 関数の名前と、引数リストを保存します。
            FunctionInfo functionInfo = { functionName, argumentList };

            functionScript = { variableName, functionInfo };
        }
    }
    void TextScriptAnalysis::makeNovelScript( )
    {
        novelScript.novel = tagWithData.novel;
    }
}
