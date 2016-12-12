#include "ScriptVoice.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

namespace User
{
    ScriptVoice::ScriptVoice( cocos2d::Layer * layer, std::string const& dir )
        : ScriptBase( layer )
        , dir( dir )
    {
        REGIST_FUNC( ScriptVoice, play );
    }
    SCRIPT( ScriptVoice::play )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string file = dir + args[0] + u8".mp3";
            if( id != 0 ) CocosDenshion::SimpleAudioEngine::getInstance( )->stopEffect( id );
            id = CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( file.c_str( ) );
        }
        break;
        default:
            break;
        }
    }
}
