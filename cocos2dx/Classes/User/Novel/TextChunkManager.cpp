#include "TextChunkManager.h"

USING_NS_CC;

namespace User
{
    TextChunkManager::TextChunkManager( )
    {
        gotoNext( );
    }
    TextChunkManager::~TextChunkManager( )
    {

    }
    bool TextChunkManager::isNovelFinished( )
    {
        return work->isReadFinished( );
    }
    void TextChunkManager::make( std::string const & novelPath )
    {
        textData.makeData( novelPath );
    }
    void TextChunkManager::select( std::string const & selectName )
    {
        textData.setNextChild( selectName );
    }
    void TextChunkManager::textRead( )
    {
        while ( delayTime == 0.0 )
        {
            // テキストを読み始めます。
            if ( !textPartyRead( ) )
            {
                if ( novelEndCallBack ) novelEndCallBack( );
                break;
            }

            // 読み込み終了なら
            if ( work->isReadFinished( ) )
            {
                if ( readEndCallBack ) readEndCallBack( );
                break;
            }
        }
    }
    bool TextChunkManager::textPartyRead( )
    {
        if ( !work->isReadFinished( ) && !textData.isEmpty( ) )
        {
            work->insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
            return true;
        }
        return false;
    }
    NovelData const& TextChunkManager::getNovelData( )
    {
        return work->getNovelData( );
    }
    std::vector<TextChunk> const & TextChunkManager::getTextChunk( )
    {
        return textChunk;
    }
    void TextChunkManager::updateDelay( float delta )
    {
        delayTime = std::max( delayTime - delta, 0.0 );
    }
    void TextChunkManager::setDelayTime( double delay )
    {
        delayTime = std::max( delay, 0.0 );
    }
    void TextChunkManager::gotoNext( )
    {
        textChunk.emplace_back( this );
        work = &textChunk.back( );
    }
}
