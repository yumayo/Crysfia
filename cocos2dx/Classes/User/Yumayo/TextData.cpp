#include "TextData.h"

#include "cocos2d.h"

#include "TextScriptReader.h"
#include "TextScriptAnalysis.h"

USING_NS_CC;

namespace User
{
    void spaceErase( std::string & lineString )
    {
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
    DebugWithLineData TextData::getLineMoved( )
    {
        DebugWithLineData ret;
        if ( work->data.empty( ) )
        {
            if ( work->parentPointer )
            {
                work = work->parentPointer;
                ret = work->data.front( );
                work->data.pop_front( );
            }
        }
        else
        {
            ret = work->data.front( );
            work->data.pop_front( );
        }
        return ret;
    }
    bool TextData::isEmpty( )
    {
        return !work->parentPointer && work->children.empty( ) && work->data.empty( );
    }
    void TextData::clear( )
    {
        chunk.children.clear( );
        chunk.data.clear( );
        chunk.parentPointer = nullptr;
    }
    void TextData::makeData( std::string fileName )
    {
        clear( );
        this->fileName = fileName;
        work = &chunk;

        auto fileUtils = FileUtils::getInstance( );
        auto str = fileUtils->getStringFromFile( fileUtils->fullPathForFilename( "res/data/" + fileName ) );

        size_t stringPosition = 0;
        size_t findPosition = 0;
        size_t lineNumber = 1; // 普通のテキストエディタでは行番号は「1」から始まるので。
        const std::string eolString = u8"\r\n";
        const size_t eolSize = std::string( eolString ).size( );
        while ( findPosition != std::string::npos )
        {
            findPosition = str.find( eolString, stringPosition );
            tidydiness( str.substr( stringPosition, findPosition - stringPosition ), lineNumber );
            stringPosition = findPosition + eolSize;
            lineNumber += 1;
        }

        for ( auto& line : work->data )
        {
            log( "%s", line.lineData.c_str( ) );
        }
    }
    void TextData::setNextChild( std::string const & selectName )
    {
        auto error = [ &, this ] ( std::string const& errorString )
        {
            auto& debugData = work->data.back( ).debugData;
            std::string str;
            str += "[variableError : " + errorString + "]";
            str += "[file:" + debugData.fileName + "]";
            str += "[line:" + std::to_string( debugData.lineNumber ) + "]";
            throw( str );
        };

        auto itr = work->children.find( selectName );
        if ( itr != work->children.cend( ) )
        {
            work = &itr->second;
        }
        else
        {
            error( "選択肢の対応先が見つかりません。" );
        }
    }
    void TextData::tidydiness( std::string lineString, size_t lineNumber )
    {
        ScriptDebugData debugData;
        debugData.fileName = fileName;
        debugData.lineNumber = lineNumber;

        auto commentErased = lineString;
        commentErase( commentErased );
        alignFirst( commentErased );

        auto scriptPosition = commentErased.find( u8"@", 0 );

        // スクリプトデータを作ります。
        DebugWithLineData lineData;
        // デバッグデータはノベルデータとスクリプトデータで共通なので、先に詰め込みます。
        lineData.debugData = debugData;

        // スクリプトデータが見つかった場合。
        if ( scriptPosition != std::string::npos )
        {
            auto novelString = commentErased.substr( 0, scriptPosition );
            auto scriptString = commentErased.substr( scriptPosition );

            // ノベルデータが含まれている場合
            if ( novelString != u8"" )
            {
                lineData.lineData = novelString;
                work->data.emplace_back( lineData );
            }

            lineData.lineData = scriptString;
            // スクリプトデータの中にプリプロセス命令が合った場合に割り込み処理をします。
            if ( !isPreprocess( lineData ) ) work->data.emplace_back( lineData );
        }
        // ノベルデータだけの場合
        else if ( commentErased != u8"" )
        {
            lineData.lineData = commentErased;
            work->data.emplace_back( lineData );
        }
    }
    bool TextData::isPreprocess( DebugWithLineData const & debugWithLineData )
    {
        TextScriptReader scriptReader;
        TextScriptAnalysis scriptAnalysis;
        scriptAnalysis.makeScript( scriptReader.createTagWithData( debugWithLineData ) );

        auto error = [ &, this ] ( std::string const& errorString )
        {
            auto& debugData = scriptAnalysis.getTagWithData( ).debugData;
            std::string str;
            str += "[variableError : " + errorString + "]";
            str += "[file:" + debugData.fileName + "]";
            str += "[line:" + std::to_string( debugData.lineNumber ) + "]";
            throw( str );
        };

        try
        {
            if ( scriptAnalysis.getTag( ) == TagWithData::Tag::FUN )
            {
                auto& func = scriptAnalysis.getFunctionScript( );
                if ( func.variable == u8"sys" )
                {
                    if ( func.functionInfo.name == u8"import" )
                    {
                        import( func.functionInfo.argumentList );
                        return true;
                    }
                    else if ( func.functionInfo.name == u8"beginland" )
                    {
                        beginland( func.functionInfo.argumentList );
                        return true;
                    }
                    else if ( func.functionInfo.name == u8"endland" )
                    {
                        endland( func.functionInfo.argumentList );
                        return true;
                    }
                }
            }
        }
        catch ( char const* errorString )
        {
            error( errorString );
        }

        return false;
    }
    void TextData::import( ArgumentList const& args )
    {
        if ( args.size( ) != 1 ) throw( "importのファイルは一つでないといけません。" );

        TextData textData;
        textData.makeData( args[0] );
        work->data.insert( work->data.cend( ), textData.work->data.cbegin( ), textData.work->data.cend( ) );
        work->children.insert( textData.work->children.cbegin( ), textData.work->children.cend( ) );
    }
    void TextData::beginland( ArgumentList const& args )
    {
        if ( args.size( ) != 1 ) throw( "beginlandのタグは一つでないといけません。" );

        work->children.insert( std::make_pair( args[0], TextChankData( work ) ) );
        work = &work->children[args[0]];
    }
    void TextData::endland( ArgumentList const& args )
    {
        if ( !work->parentPointer ) throw( "endlandに対応するbeginlandが見つかりませんでした。" );

        work = work->parentPointer;
    }
}