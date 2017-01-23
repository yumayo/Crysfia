# ifndef __SoundManager__
# define __SoundManager__

# include "cocos2d.h"

namespace User
{
	class SoundManager
	{
	public:

		enum BgmType
		{
			BGM_A = 0,
			NONE
		};
		enum SeType
		{
			SE_A = 0,
		};

		static SoundManager* getInstance();
		SoundManager();
		~SoundManager();

		void init();
		void playBGM(BgmType type, bool loop = true);
		void playSE(SeType type);

		void setVolume(float volume);
		void saveParams();

		CC_PROPERTY(float, bgmVolume, BgmVolume);
		CC_PROPERTY(float, seVolume, SeVolume);
		CC_PROPERTY(bool, mute, Mute);

	private:

		struct BgmData
		{
			BgmData()
			{
				bgmId = -1;
				type = NONE;
				isPlaying = false;
			}
			int bgmId;		//ID
			BgmType type;	//ZBGMのタイプ
			bool isPlaying;	//再生中かどうか
		};

		std::string getBgmPath(BgmType type);
		std::string getSePath(SeType type);

		BgmData bgmData;
		std::vector<int> seList;

		float getMuteBgmVolume() { return mute ? 0.0f : bgmVolume; };
		float getMuteSeVolume() { return mute ? 0.0f : seVolume; }

		void finishCallBack(int audioID, std::string filePath);

	};
}

# endif // __SoundManager__
