#include "StringUtil.h"

#include <ctype.h>

namespace User
{
    double StringUtil::string_double( std::string const & str )
    {
        char* endptr;
        char const* s = str.c_str( );
        auto errorBuf = errno;
        errno = 0;
        auto ret = strtod( s, &endptr );
        auto error = errno;
        errno = errorBuf;
        if ( 0 != error || ( 0.0 == ret && s == endptr ) )
        {
            throw( "無効な数値です。" );
        }
        return ret;
    }
    int StringUtil::string_int( std::string const & str )
    {
        char* endptr;
        char const* s = str.c_str( );
        auto errorBuf = errno;
        errno = 0;
        auto ret = strtol( s, &endptr, 10 );
        auto error = errno;
        errno = errorBuf;
        if ( 0 != error || ( 0 == ret && s == endptr ) )
        {
            throw( "無効な数値です。" );
        }
        return ret;
    }
    bool StringUtil::string_bool( std::string const & str )
    {
        if ( str == u8"false" )
        {
            return false;
        }
        else if ( str == u8"true" )
        {
            return true;
        }
    }
    float StringUtil::string_float( std::string const & str )
    {
        char* endptr;
        char const* s = str.c_str( );
        auto errorBuf = errno;
        errno = 0;
        auto ret = strtof( s, &endptr );
        auto error = errno;
        errno = errorBuf;
        if ( 0 != error || ( 0.0F == ret && s == endptr ) )
        {
            throw( "無効な数値です。" );
        }
        return ret;
    }
}
