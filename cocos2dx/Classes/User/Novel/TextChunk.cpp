#include "TextChunk.h"

#include "TextChunkManager.h"
#include "ScriptStaticData.h"
#include "ScriptSystem.h"

#include <algorithm>
#include <sstream>

namespace User
{
    TextChunk::TextChunk( TextChunkManager * manager )
        : novelIndex( ScriptSystem::novelIndex )
        , manager( manager )
    {
        novelIndex = 0;
    }
    TextChunk::~TextChunk( )
    {

    }
    void TextChunk::insertScript( TagWithData const& tagWithData )
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
            try
            {
                pushFunction( );
            }
            catch ( char const* str )
            {

            }
            break;
        default:
            return;
            break;
        }
    }
    bool TextChunk::isReadFinished( )
    {
        return novelIndex == novelData.size( );
    }
    NovelData const& TextChunk::getNovelData( )
    {
        return novelData;
    }
    void TextChunk::pushVariable( )
    {
        auto data = scriptAnalysis.getVariableScript( );
        manager->variableScriptData.insert( std::make_pair( data.variable, data.currentStatus ) );
    }
    void TextChunk::pushFunction( )
    {
        auto data = scriptAnalysis.getFunctionScript( );

        for ( auto& arg : data.functionInfo.argumentList )
        {
            if ( arg.find( u8"$" ) != std::string::npos )
            {
                auto itr = manager->variableScriptData.find( arg );
                if ( itr != manager->variableScriptData.cend( ) ) arg = itr->second;
                else errorSStream( "指定した変数が存在しません。", scriptAnalysis.getTagWithData( ).debugData );
            }
        }

        // スクリプトデータから変数と一致する関数を呼び出します。
        ScriptStaticData::run( data );

        functionScriptData.insert( std::make_pair( data.variable, data.functionInfo ) );
    }
    void TextChunk::pushNovel( )
    {
        novelIndex = std::min( novelIndex + 1U, novelData.size( ) );

        novelData[novelIndex - 1] = scriptAnalysis.getNovelScript( ).novel;
    }
}
