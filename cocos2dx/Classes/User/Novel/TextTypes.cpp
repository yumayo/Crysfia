
# include "TextTypes.hpp"

# include <sstream>

# include "cocos2d.h"

USING_NS_CC;

namespace User
{
    void writeDebugLog( std::string const& dataStr )
    {
        auto fileUtil = FileUtils::getInstance( );
        
        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            std::string savepath = path + "debugLog.txt";
            fileUtil->writeStringToFile( dataStr, savepath );
        }
    }

    void errorSStream( std::string const& error, ScriptDebugData const& debugData )
    {
        std::stringstream stream;
        stream << "[エラー内容 : " + error + "]" << std::endl;
        stream << "[ファイル名 : " + debugData.fileName + "]" << std::endl;
        stream << "[行番号 : " + std::to_string( debugData.lineNumber ) + "]" << std::endl;
        throw( stream.str( ) );
    }
}