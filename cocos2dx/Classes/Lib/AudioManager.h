/****************************************************************************
 Copyright (c) 2016 Yuji Toki(tokineco)
 - MIT license
****************************************************************************/
#ifndef __AudioManager__
#define __AudioManager__

#include "cocos2d.h"

class AudioManager {

private:

    enum AudioType {
        BGM,
        SE,
        VOICE
    };

    enum FadeType {
        NONE = 0,
        FADE_IN = 1,
        FADE_OUT = 2,
        FADE_IN_RESUME = 3,
        FADE_OUT_PAUSE = 4
    };

public:
    /**
     * チャンク番号を数字で入力するのはいけ好かない感じがするのでenumで
     */
    enum Chunk
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
        End
    };
private:

    AudioManager( );
    static AudioManager* _instance;

    // update実行用
    static cocos2d::Scheduler* _scheduler;

    // BGMファイルリスト
    std::map<std::string, std::string> _bgmList;
    // BGMファイル区間設定リスト
    struct BgmLoopParams {
        float startPos;
        float endPos;
        bool isLoopInterval;
    };
    std::map<std::string, BgmLoopParams> _bgmLoopList;
    // SEファイルリスト
    std::map<std::string, std::string> _seList;

    // SE用チャンク
    int _chunk[Chunk::End];

    // BGMは1種類のみ
    int _bgmId = -1;
    // 同じファイル名の場合は無視
    std::string _bgmFileName = "";

    // オーディオ管理ファイルを使用する場合はそのファイルパス
    CC_SYNTHESIZE( std::string, _audioListFile, AudioListFile );

    // BGM音量
    float  _bgmVolume;
    // SE音量
    float _seVolume;

    // BGMフェード関連
    FadeType _fadeCondition;
    float _bgmFadeVolumeFrom;
    float _bgmFadeVolumeTo;
    float _bgmFadeVolumeNow;
    float _bgmFadeTime;
    bool _stopBgmReleaseFlg;

    //==========================

public:

    ~AudioManager( );
    static AudioManager* getInstance( );
    static void deleteInstance( );

    // 毎フレーム実行
    virtual void update( float dt );

    // オーディオ管理ファイルを読み込む
    bool readAudioListFile( std::string const& fileName );
    // AudioEngine全てのキャッシュを削除する
    void releaseAll( );

    // BGMとSEの音量の初期化
    void initVolume( float bgmVolume, float seVolume );

    // BGMのPreLoad
    void preloadBgm( std::string const& baseName );
    // BGMの再生
    int playBgm( std::string const& baseName, float fadeTime = 0, bool loop = true );
    int playBgm( std::string const& baseName, float fadeTime, bool loop, float volume );
    // BGMを一時停止する
    void pauseBgm( float fadeTime = 0 );
    // BGMをリジューム再生する
    void resumeBgm( float fadeTime = 0 );
    // BGMを停止する
    // Arg2 - release : キャッシュを破棄する場合はtrue
    void stopBgm( float fadeTime = 0, bool release = true );
    // BGMが再生されているかどうか
    bool isPlayingBgm( );
    // BGMの音量を変更する
    // Arg2 - save : 変数_bgmVolumeに保存する場合はtrue
    void setBgmVolume( float volume, bool save = true );
    // BGMの音量を取得する
    float getBgmVolume( );
    // BGMのキャシュを解放する
    void releaseBgm( );

    // 効果音のPreLoad
    void preloadSe( std::string const& baseName );
    // 効果音を再生する
    // Args2 - chunkNo : チャンクを指定すると同じチャンク番号が指定された場合は、前の音を上書きする
    int playSe( std::string const& baseName, int chunkNo );
    int playSe( std::string const& baseName, int chunkNo, bool loop, float volume );
    int playSe( std::string const& baseName, bool loop = false );
    int playSe( std::string const& baseName, bool loop, float volume );
    // 効果音を停止する
    void stopSe( int soundId );
    // 効果音の音量を変更する
    void setSeVolume( float volume );
    // 効果音の音量を取得する
    float getSeVolume( );
    // 効果音のキャッシュを解放する
    void releaseSe( std::string const& baseName );

    // AudioEngineを解放する
    void endAudioEngine( );

    /**
     * VOICEの追加
     * SEと機構は同じ
     * 基本的にはボリューム差別化を図るためのもの
     * <!--chunkはseのものと共有して使われているので注意-->
     */
    float _voiceVolume;
    std::map<std::string, std::string> _voiceList;
     // 効果音のPreLoad
    void preloadVoice( std::string const& baseName );
    // 効果音を再生する
    // Args2 - chunkNo : チャンクを指定すると同じチャンク番号が指定された場合は、前の音を上書きする
    int playVoice( std::string const& baseName, Chunk chunkNo );
    int playVoice( std::string const& baseName, Chunk chunkNo, bool loop, float volume );
    int playVoice( std::string const& baseName, bool loop = false );
    int playVoice( std::string const& baseName, bool loop, float volume );
    // 効果音を停止する
    void stopVoice( int soundId );
    // 効果音の音量を変更する
    void setVoiceVolume( float volume );
    // 効果音の音量を取得する
    float getVoiceVolume( );
    // 効果音のキャッシュを解放する
    void releaseVoice( std::string const& baseName );

    void stopAllBgm( );
    void stopAllSe( );
    void stopAllVoice( );
private:
    std::vector<int> playSeIds;
    std::vector<int> playVoiceIds;


private:
    // 環境に応じて拡張子付きファイル名に変換する
    std::string getFileName( AudioType type, std::string baseName );

    // pauseBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
    void pauseBgmEngine( );

    // stopBgmの実行(fadeなし、またはupdateによるフェード後に実行される)
    void stopBgmEngine( bool release = true );

    // モバイルデバイスかどうか
    bool isMobileDevice( );
};

#endif /* defined(__AudioManager__) */
