//
//  MoveTiledSprite.h
//  DaikonThrows
//  タイル状に同じものを並べて動かすよ
//  Created by Kazuki Oda on 2013/11/07.
//
//

#ifndef DaikonThrows_MoveTiledSprite_h
#define DaikonThrows_MoveTiledSprite_h
#include "cocos2d.h"
class MoveTiledSprite : public cocos2d::CCSpriteBatchNode{
	const std::string m_tilename;
	float m_speed; //スピード
	float m_dx; //x軸の動き
	float m_dy; //y軸の動き
	cocos2d::CCSize m_spriteSize; //ひとつの画像の大きさ
	bool m_isSpriteFrame; //スプライトフレームを使用するかどうか
	CC_SYNTHESIZE(cocos2d::CCSize , m_size, VisibleSize); //画面のサイズ
	enum tag{
		kTagDefault = 1,
		kTagSprite = 1000000,
	};
	typedef enum rectType{
		type_inner ,
		type_outer ,
		type_border ,
	}rectType;
	
	struct TilePos{
		int x;
		int y;
		TilePos(int $x , int $y){ x = $x; y = $y; }
		TilePos(const TilePos &$tile){
			x = $tile.x;
			y = $tile.y;
		}
		void add(int $x , int $y){
			x += $x;
			y += $y;
		}
	};
	
public:
	MoveTiledSprite(const std::string &$tilename):m_tilename($tilename),m_spriteSize(0,0){};
	/**
	 * テクスチャアトラスから作成する
	 * @$filename = テクスチャアトラスの画像名
	 * @$tileFileName = plistでの画像名
	 * @$speed = スピード
	 * @$angle = 動かす角度
	 */
	static MoveTiledSprite* createWithSpriteFrame(const char* $fileName , const char* $tileFileName , float $speed , float $angle);
	/**
	 * 画像から作成する
	 * @$filename = 画像名
	 * @$speed = スピード
	 * @$angle = 動かす角度
	 */
	static MoveTiledSprite* createWithSprite(const char* $fileName , float $speed , float $angle);
	virtual bool init(const char* $fileName , float $speed , float $angle , bool $isSpriteFrame);
	virtual void update(float $df);
	virtual ~MoveTiledSprite();
protected:
	virtual void setTile();
	virtual cocos2d::CCSprite* makeSprite();
	virtual int getSpriteTag(int $x , int $y);
	virtual TilePos getTilePos(int $tag);
	virtual void makeAroundTile(cocos2d::CCSprite* $sprite);
	virtual void makeTile(int tag , const cocos2d::CCPoint &$pos);
	//はみでてたら削除したりとか
	virtual void moveSprite(cocos2d::CCSprite* node);
	virtual rectType typeOfSprite(cocos2d::CCNode* node);
};


#endif
