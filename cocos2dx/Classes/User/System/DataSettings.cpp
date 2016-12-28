#include "DataSettings.h"

#include "../Novel/INIReader.h"
#include "../Novel/INIWriter.h"
#include "../Novel/StringUtil.h"

USING_NS_CC;

namespace User
{
    void iniDataRead( INIReader & reader, std::string const& name )
    {
        auto file = FileUtils::getInstance( );
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
        {
            reader.read( file->getWritablePath( ) + name );
        }
        else
        {
            reader.read( name );
        }
    }
    void iniDataRead( INIReader & reader, std::string const & name, std::string const & defalutDirectory )
    {
        auto file = FileUtils::getInstance( );
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
        {
            reader.read( file->getWritablePath( ) + name );
        }
        else
        {
            reader.read( defalutDirectory + name );
        }
    }
    void userDefaultLoading( std::string const& name )
    {
        CC_ASSERT( !"未実装。" );
    }
    void userDefaultSaveing( std::string const& name )
    {
        CC_ASSERT( !"未実装。" );
    }
    void userDefaultSetup( )
    {
        auto data = UserDefault::getInstance( );
        if ( !data->getBoolForKey( u8"INITDATA", false ) )
        {
            INIReader reader;
            iniDataRead( reader, u8"res/data/userDefault.ini" );

            std::map<std::string, std::function<void( std::map<std::string, std::string> )>> calls;

            calls.insert( { u8"bool", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setBoolForKey( value.first.c_str( ), StringUtil::string_value<bool>( value.second ) );
            } } );
            calls.insert( { u8"int", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setIntegerForKey( value.first.c_str( ), StringUtil::string_value<int>( value.second ) );
            } } );
            calls.insert( { u8"float", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setFloatForKey( value.first.c_str( ), StringUtil::string_value<float>( value.second ) );
            } } );
            calls.insert( { u8"string", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setStringForKey( value.first.c_str( ), StringUtil::string_value<std::string>( value.second ) );
            } } );

            for ( auto& tag : reader.getData( ) )
            {
                auto itr = calls.find( tag.first );
                if ( itr != calls.end( ) )
                {
                    itr->second( tag.second );
                }
            }
            data->setBoolForKey( u8"INITDATA", true );
        }
    }
    void userDefaultForceSetup( )
    {
        UserDefault::getInstance( )->setBoolForKey( u8"INITDATA", false );
        userDefaultSetup( );
    }
    std::string getLocalReadPath( std::string const & name )
    {
        auto file = FileUtils::getInstance( );
        std::string path;
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
            path = file->getWritablePath( ) + name;
        else
            path = name;
        return path;
    }
    std::string getLocalReadPath( std::string const & name, std::string const & directory )
    {
        auto file = FileUtils::getInstance( );
        std::string path;
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
            path = file->getWritablePath( ) + name;
        else
            path = directory + name;
        return path;
    }
    void writeUserLocal( std::string const & data, std::string const & name )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeStringToFile( data, path + name );
        }
    }
    void writeUserLocal( std::string const & data, std::string const & name, std::string const & directory )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeStringToFile( data, path + directory + name );
        }
    }
    void writeDataUserLocal( cocos2d::Data const & data, std::string const & name )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeDataToFile( data, path + name );
        }
    }
    void writeDataUserLocal( cocos2d::Data const & data, std::string const & name, std::string const & directory )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeDataToFile( data, path + directory + name );
        }
    }
}