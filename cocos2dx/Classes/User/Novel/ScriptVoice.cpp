#include "ScriptVoice.h"

#include "../../Lib/AudioManager.h"

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
            AudioManager::getInstance( )->playVoice( dir + args[0] + u8".mp3", AudioManager::Chunk::_15 );
        }
        break;
        default:
            break;
        }
    }
}
