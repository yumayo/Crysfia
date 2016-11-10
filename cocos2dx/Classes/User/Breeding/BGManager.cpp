#include "BGManager.h"
#include "cocos2d/external/json/rapidjson.h"
#include "cocos2d/external/json/document.h"
USING_NS_CC;

namespace User
{
	BGManager::BGManager()
	{

	}
	BGManager::~BGManager()
	{
	}

	bool BGManager::init()
	{

		auto size = Director::getInstance()->getVisibleSize();

		auto sprite = Sprite::create("res/texture/背景市場.png");
		sprite->setPosition(size / 2);
		//addChild(sprite);

		//jsonファイルの読み込み
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("jsonFile/background.json");
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
				backgrounds[i]->setPosition(size / 2);
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
