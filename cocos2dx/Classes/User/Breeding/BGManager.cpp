#include "BGManager.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace experimental;

namespace User
{
	BGManager::BGManager() :
		winSize(Director::getInstance()->getVisibleSize()),
		backgrounds(std::vector<Sprite*>()),
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		homeBgm(AudioEngine::play2d("res/sound/BGM/home.mp3"))
#else
		homeBgm(AudioEngine::play2d("res/sound/BGM/home.wav"))
#endif
	{
		
	}

	BGManager::~BGManager()
	{
		AudioEngine::stop(homeBgm);
	}

	bool BGManager::init()
	{		
		//jsonファイルの読み込み
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("res/json/background.json");
		rapidjson::Document doc;

		//jsonファイルをパース5
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());
		if (!doc.HasParseError())
		{
			const rapidjson::Value& backgroundData = doc["backgrounds"];
			for (rapidjson::SizeType i = 0; i < backgroundData.Size(); i++)
			{
				backgrounds.push_back(Sprite::create(backgroundData[i]["res"].GetString()));
				float x = backgroundData[i]["pos"]["x"].GetDouble();
				float y = backgroundData[i]["pos"]["y"].GetDouble();
				backgrounds[i]->setPosition(winSize / 2);
				backgrounds[i]->setScale(backgroundData[i]["scale"].GetDouble());
				backgrounds[i]->setOpacity(backgroundData[i]["alpha"].GetInt());
				this->addChild(backgrounds[i], -i, i);
			}
		}


		return true;
	}

	void BGManager::changeBackGround(int targetBG, int changeBG)
	{
		backgrounds[changeBG]->runAction(FadeOut::create(1));
		backgrounds[targetBG]->runAction(FadeIn::create(1));
	}

}
