#include "TextChank.h"

#include "ScriptStaticData.h"

#include <algorithm>

namespace User
{
    TextChank::TextChank( )
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

        //variableScriptData.clear( ); // �ϐ��̏������͂��Ȃ��B

        novelIndex = 0;
        for ( auto& obj : novelData ) obj = u8"";
    }
    void TextChank::makeVariableScript( )
    {
        auto data = bufferTagWithNovelStringAndRawScriptPartsData.script;

        auto values = data;
        auto variableName = data[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto currentStatusName = data[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A���̕ϐ��̎��̂��L�ڂ���Ă��܂��B

        variableScriptData.insert( std::make_pair( variableName, currentStatusName ) );
    }
    void TextChank::makeFunctionScript( )
    {
        auto data = bufferTagWithNovelStringAndRawScriptPartsData.script;

        auto values = data;
        auto variableName = data[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto functionName = data[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A�֐������L�ڂ���Ă��܂��B

        // �����Ȃ��̏ꍇ
        // ���@��֐���"()"���ȗ��ł���悤�ɂ��Ă���̂ŁB
        if ( values.size( ) == 3U )
        {
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionInfo functionInfo = { functionName, ArgumentList( ) };

            // �ŏI�I�ɁA�֐������������}�b�v�𐶐����܂��B
            functionScriptData.insert( std::make_pair( variableName, functionInfo ) );
        }
        // ��������̏ꍇ
        // "()"�𖾎��I�ɏ����Ă�OK�Ȃ悤�ɂ��Ă��܂��B
        else
        {
            auto error = [ ] ( std::string const& errorString ) { throw( "variableError : " + errorString ); };

            // �֐��̈����������c���܂��B
            values.erase( values.begin( ), values.begin( ) + 4 );
            values.pop_back( );

            // �������X�g���쐬���܂��B
            ArgumentList argumentList;
            // 2��΂��Ȃ̂́A�Ԃ�","�����邽�߁B
            // �ق�Ƃ��ɕK�v�Ȃ̂́A�����Ԃɂ�������݂̂ł��B
            for ( size_t i = 0; i < values.size( ); i += 2 )
            {
                if ( values[i].find( u8"$" ) != std::string::npos )
                {
                    auto itr = variableScriptData.find( values[i] );
                    if ( itr != variableScriptData.cend( ) ) argumentList.emplace_back( itr->second );
                    else error( "�w�肵���ϐ������݂��܂���B" );
                }
                else argumentList.emplace_back( values[i] );

            }
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionInfo functionInfo = { functionName, argumentList };

            // �ŏI�I�ɁA�֐������������}�b�v�𐶐����܂��B
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
        ScriptStaticData::runScript( functionScriptChip );
    }
}
