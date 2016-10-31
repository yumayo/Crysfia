﻿#include "TextChank.h"

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
    void TextChank::insertScript( TagWithData const& tagWithData )
    {
        scriptAnalysis.makeScript( tagWithData );

        switch ( scriptAnalysis.getTag( ) )
        {
        case TagWithData::Tag::NOV:
            pushNovel( );
            break;
        case TagWithData::Tag::VAR:
            pushVariable( );
            break;
        case TagWithData::Tag::FUN:
            pushFunction( );
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
        scriptAnalysis.clear( );

        // インデックス番号をもとに戻します。
        novelIndex = 0;

        // 関数履歴や、変数は初期化しません。
        //functionScriptData.clear( );
        //variableScriptData.clear( );

        // ノベルデータは初期化します。
        for ( auto& obj : novelData ) obj = u8"";
    }
    void TextChank::pushVariable( )
    {
        auto data = scriptAnalysis.getVariableScript( );
        variableScriptData.insert( std::make_pair( data.variable, data.currentStatus ) );
    }
    void TextChank::pushFunction( )
    {
        auto error = [ this ] ( std::string const& errorString )
        { 
            auto& debugData = scriptAnalysis.getTagWithData( ).debugData;
            std::string str;
            str += "[variableError : " + errorString + "]";
            str += "[file:" + debugData.fileName + "]";
            str += "[line:" + std::to_string( debugData.lineNumber ) + "]";
            throw( str );
        };

        auto data = scriptAnalysis.getFunctionScript( );

        for ( auto& arg : data.functionInfo.argumentList )
        {
            if ( arg.find( u8"$" ) != std::string::npos )
            {
                auto itr = variableScriptData.find( arg );
                if ( itr != variableScriptData.cend( ) ) arg = itr->second;
                else error( "指定した変数が存在しません。" );
            }
        }

        // スクリプトデータから変数と一致する関数を呼び出します。
        ScriptStaticData::run( data );

        functionScriptData.insert( std::make_pair( data.variable, data.functionInfo ) );
    }
    void TextChank::pushNovel( )
    {
        novelIndex = std::min( novelIndex + 1U, novelData.size( ) );

        novelData[novelIndex - 1] = scriptAnalysis.getNovelScript( ).novel;
    }
}
