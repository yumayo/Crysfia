#pragma once

#include <memory>
#include <string>
#include <map>

#include "INIReader.h"

namespace User
{
    class INIWriter
    {
        INIWriter( ) { /*nothing*/ }
    public:
        static void write( const std::string & filePath, INIReader const& reader );
        static void write( const std::string & filePath, std::map<std::string, std::map<std::string, std::string>> const & data );
    private:
        static std::string fieldWrite( const std::string& field );
        static bool grammarValueCheck( const std::pair < std::string, std::string >& value );
        static std::string valuesWrite( const std::pair < std::string, std::string >& values );
    };
}