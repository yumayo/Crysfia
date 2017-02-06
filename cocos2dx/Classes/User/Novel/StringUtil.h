# ifndef __StringUtil__
# define __StringUtil__

# include <string>
# include <sstream>

namespace User
{
    class StringUtil
    {
    public:
        template<typename Ty>
        static Ty string_value( std::string const& str );
        template<typename Ty>
        static std::string value_string( Ty value );
    private:
        static double string_double( std::string const& str );
        static int string_int( std::string const& str );
        static bool string_bool( std::string const& str );
        static float string_float( std::string const& str );
    };

    template<>
    inline bool StringUtil::string_value<bool>( std::string const& str )
    {
        return string_bool( str );
    }
    template<>
    inline int StringUtil::string_value<int>( std::string const & str )
    {
        return string_int( str );
    }
    template<>
    inline double StringUtil::string_value<double>( std::string const & str )
    {
        return string_double( str );
    }
    template<>
    inline float StringUtil::string_value<float>( std::string const & str )
    {
        return string_float( str );
    }
    template<>
    inline std::string StringUtil::string_value<std::string>( std::string const & str )
    {
        return str;
    }
    template<>
    inline std::string StringUtil::value_string<std::string>( std::string value )
    {
        return value;
    }
    template<>
    inline std::string StringUtil::value_string<bool>( bool value )
    {
        if ( value )
        {
            return u8"true";
        }
        else
        {
            return u8"false";
        }
    }
    template<>
    inline std::string StringUtil::value_string<int>( int value )
    {
        std::stringstream stream;
        stream << value;
        return stream.str( );
    }
    template<>
    inline std::string StringUtil::value_string<double>( double value )
    {
        std::stringstream stream;
        stream << value;
        return stream.str( );
    }
    template<>
    inline std::string StringUtil::value_string<float>( float value )
    {
        std::stringstream stream;
        stream << value;
        return stream.str( );
    }
}

# endif // __StringUtil__