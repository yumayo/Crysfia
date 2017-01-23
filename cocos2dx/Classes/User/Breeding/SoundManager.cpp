#include "SoundManager.h"
USING_NS_CC;
using namespace experimental;

namespace User
{
	static SoundManager* instance;

	SoundManager * SoundManager::getInstance()
	{
		if (!instance) 
		{
			instance = new SoundManager();
			instance->init();
		}
		return instance;
	}

	SoundManager::SoundManager( ):
		bgmData(BgmData()),
		seList(std::vector<int>()),
		bgmVolume(1.0f),
		seVolume(1.0f)
    {
        
    }
	SoundManager::~SoundManager() {}

	void SoundManager::init()
	{
		//mute = UserDefault::getInstance()->getBoolForKey("mute")
	}
	void SoundManager::playBGM(BgmType type, bool loop)
	{
	}
	void SoundManager::playSE(SeType type)
	{
	}
	void SoundManager::setVolume(float volume)
	{
	}
	void SoundManager::saveParams()
	{
	}
	std::string SoundManager::getBgmPath(BgmType type)
	{
		return std::string();
	}
	std::string SoundManager::getSePath(SeType type)
	{
		return std::string();
	}
	void SoundManager::finishCallBack(int audioID, std::string filePath)
	{
	}
}
