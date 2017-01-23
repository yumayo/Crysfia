#pragma once

#include <memory>
#include <string>
#include <map>

namespace User
{
    class INIReader
    {
        std::map<std::string, std::map<std::string, std::string>> data;
    public:
        INIReader( );
        INIReader( const std::string& filePath );
        void read( const std::string& filePath );
        std::map<std::string, std::string>& findField( const std::string& field );
        std::map<std::string, std::string>& operator[]( const std::string& field ) { return findField( field ); }
        std::map<std::string, std::map<std::string, std::string>> const& getData( ) { return data; }
    private:
        static std::string spaceErase( std::string lineStr );
        static std::string commentErase( std::string lineStr );
        static bool findLineField( std::string lineStr );
        static bool findValue( std::string lineStr );
        static std::string fieldName( std::string lineStr );
        static std::pair<std::string, std::string> fieldValue( std::string lineStr );
    private:
        friend class INIWriter;
    };
}