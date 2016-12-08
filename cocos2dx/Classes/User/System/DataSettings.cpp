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
    void userDefaultLoading( )
    {
        INIReader reader;
        iniDataRead( reader, u8"system.ini", u8"res/data/" );

        auto data = UserDefault::getInstance( );
        for ( auto& tag : reader.getData( ) )
        {
            if ( tag.first == u8"bool" )
            {
                for ( auto& value : tag.second )
                    data->setBoolForKey( value.first.c_str( ), StringUtil::string_value<bool>( value.second ) );
            }
            else if ( tag.first == u8"int" )
            {
                for ( auto& value : tag.second )
                    data->setIntegerForKey( value.first.c_str( ), StringUtil::string_value<int>( value.second ) );
            }
        }
    }
    void userDefaultSaveing( )
    {
        INIReader reader;
        iniDataRead( reader, u8"system.ini", u8"res/data/" );

        auto data = UserDefault::getInstance( );
        for ( auto& tag : reader.getData( ) )
        {
            if ( tag.first == u8"bool" )
            {
                for ( auto& value : tag.second )
                    reader[tag.first][value.first] = StringUtil::value_string<bool>( data->getBoolForKey( value.first.c_str( ) ) );
            }
            else if ( tag.first == u8"int" )
            {
                for ( auto& value : tag.second )
                    reader[tag.first][value.first] = StringUtil::value_string<int>( data->getIntegerForKey( value.first.c_str( ) ) );
            }
        }

        INIWriter::write( u8"system.ini", reader );
    }
    void userDefaultSetup( )
    {
        auto data = UserDefault::getInstance( );
        if ( !data->getBoolForKey( u8"INITDATA", false ) )
        {
            INIReader reader( u8"res/data/system.ini" );
            for ( auto& tag : reader.getData( ) )
            {
                if ( tag.first == u8"bool" )
                {
                    for ( auto& value : tag.second )
                        data->setBoolForKey( value.first.c_str( ), StringUtil::string_value<bool>( value.second ) );
                }
                else if ( tag.first == u8"int" )
                {
                    for ( auto& value : tag.second )
                        data->setIntegerForKey( value.first.c_str( ), StringUtil::string_value<int>( value.second ) );
                }
            }
            data->setBoolForKey( "INITDATA", true );
        }
    }
}