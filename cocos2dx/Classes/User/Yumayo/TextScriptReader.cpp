#include "TextScriptReader.h"

#include "TextData.h"

#include <functional>
#include <algorithm>
#include <sstream>

namespace User
{
    TagWithData TextScriptReader::createTagWithData( DebugWithLineData const& debugWithLineData )
    {
        this->debugWithLineData = debugWithLineData;

        // ������̐擪��"@"������ꍇ�̓X�N���v�g
        if ( debugWithLineData.lineData[0] == '@' ) makeScriptData( );
        // �����łȂ��ꍇ�̓m�x���f�[�^�ł��B
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

            // �\�������������ꍇ�́A�ǂ�ǂ񕪊����Ă����܂��B
            if ( findSyntaxItr->isFind )
            {
                partsAdd( findSyntaxItr->position );
                scriptParts.emplace_back( findSyntaxItr->partsString );
                scriptLine = scriptLine.substr( findSyntaxItr->position + std::string( findSyntaxItr->partsString ).size( ) );

                disassembly( );
            }
            // �\����������Ȃ������ꍇ�́A�c����������ǉ����ďI���ł��B
            else
            {
                partsAdd( findSyntaxItr->position );
            }
        };

        disassembly( );

        try
        {
            syntaxCheck( scriptParts );
        }
        catch ( char const* str )
        {

        }

        // �ϐ����̂Ƃ����"$"�}�[�N������ΐV�����ϐ��Ƃ��č쐬�o���܂��B
        if ( scriptParts[0].find( u8"$" ) != std::string::npos )
        {
            tagWithData = { TagWithData::Tag::VAR, debugWithLineData.debugData, scriptParts, u8"" };
        }
        // �Ⴄ�Ȃ�A�֐��Ăяo���ɂȂ�܂��B
        else
        {
            tagWithData = { TagWithData::Tag::FUN, debugWithLineData.debugData, scriptParts, u8"" };
        }
    }
    void TextScriptReader::syntaxCheck( StringArray const & scriptParts )
    {
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

        if ( parts.size( ) < 3U ) errorSStream( "�Œ�� [@ NAME : RUN] �̌`�ŋL�����Ă��������B", debugWithLineData.debugData );

        if ( parts[1] != u8":" ) errorSStream( "�y�A�\���Ɍ�肪����܂��B", debugWithLineData.debugData );

        if ( parts[0].find( u8"$" ) != std::string::npos ) tag = TagWithData::Tag::VAR;
        else tag = TagWithData::Tag::FUN;

        switch ( tag )
        {
        case User::TagWithData::Tag::VAR:
            if ( 3U != parts.size( ) ) errorSStream( "�ϐ��̎��͈̂�łȂ��Ƃ����܂���B", debugWithLineData.debugData );
            if ( !isValue( parts[2] ) ) errorSStream( "�ϐ��錾�ɑ΂��鐔�����s���Ȓl�ł��B", debugWithLineData.debugData );
            break;
        case User::TagWithData::Tag::FUN:
            if ( 3U < parts.size( ) )
            {
                if ( parts[3] != u8"(" ) errorSStream( "�֐��̈����\�����Ԉ���Ă��܂��B", debugWithLineData.debugData );
                if ( parts.back( ) != u8")" ) errorSStream( "�֐��̈������X�g�̍Ō�� \")\" ������܂���B", debugWithLineData.debugData );

                for ( size_t i = 5; i < parts.size( ) - 1; i += 2 )
                {
                    if ( parts[i] != u8"," ) errorSStream( "�֐��̈������X�g������ł͂���܂���B", debugWithLineData.debugData );
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