#include "DiaryLabelData.h"

USING_NS_CC;

namespace User
{
DiaryLabelData::DiaryLabelData( std::string relativePath )
{
    // データを読み取ります。
    // 改行コードを指定して一行づつvectorに詰めていきます。
    auto path = FileUtils::getInstance( )->fullPathForFilename( "res/diary/" + relativePath );
    auto str = FileUtils::getInstance( )->getStringFromFile( path );
    size_t stringPosition = 0;
    size_t findPosition = 0;
    const std::string EOL = u8"\n";
    const size_t EOLSIZE = std::string( EOL ).size( );
    std::vector<std::string> data;
    while ( findPosition != std::string::npos )
    {
        findPosition = str.find( EOL, stringPosition );
        data.emplace_back( str.substr( stringPosition, findPosition - stringPosition ) );
        stringPosition = findPosition + EOLSIZE;
    }
    assert( !data.empty( ) );

    // 最後に文字が合ったインデックスを保存。
    size_t lastMojiIndex = 0;
    for ( size_t i = 0; i < data.size( ); ++i )
    {
        if ( !data[i].empty( ) ) lastMojiIndex = i;
    }
    // 最後に余分な改行コードが合った場合それを取り除きます。
    if ( ( data.size( ) - 1 ) != lastMojiIndex )
    {
        data.resize( lastMojiIndex + 1 );
    }

    // 先頭行はタイトルとして扱います。
    assert( 1 <= data.size( ) );
    std::string title = data.front( );
    data.erase( data.begin( ) );

    // 次の行は空行なのでカットします。
    assert( 1 <= data.size( ) );
    data.erase( data.begin( ) );

    this->title = std::move( title );
    this->labels = std::move( data );
}
}
