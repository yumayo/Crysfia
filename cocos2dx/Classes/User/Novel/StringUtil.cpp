#include "StringUtil.h"

#include <stdlib.h>

namespace User
{
double StringUtil::string_double( std::string const & str )
{
    return (double)atof( str.c_str( ) );
}
int StringUtil::string_int( std::string const & str )
{
    return atoi( str.c_str( ) );
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
    return atof( str.c_str( ) );
}
}
