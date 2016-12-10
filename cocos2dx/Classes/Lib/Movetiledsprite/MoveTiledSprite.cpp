//
//  MoveTiledSprite.cpp
//  DaikonThrows
//
//  Created by Kazuki Oda on 2013/11/07.
//
//

#include "MoveTiledSprite.h"
using namespace cocos2d;
MoveTiledSprite::~MoveTiledSprite(){
}

//テクスチャアトラスから作成
MoveTiledSprite* MoveTiledSprite::createWithSpriteFrame(const char *$fileName, const char *$tileFileName, float $speed, float $angle){
	MoveTiledSprite* tile = new MoveTiledSprite($tileFileName);
	if(tile && tile->init($fileName, $speed, $angle , true)){
		tile->autorelease();
		return tile;
	}
	CC_SAFE_DELETE(tile);
	tile = NULL;
	return NULL;
}

//通常の画像から作成
MoveTiledSprite* MoveTiledSprite::createWithSprite(const char *$fileName, float $speed, float $angle){
	MoveTiledSprite* tile = new MoveTiledSprite($fileName);
	if(tile && tile->init($fileName, $speed, $angle , false)){
		tile->autorelease();
		return tile;
	}
	CC_SAFE_DELETE(tile);
	tile = NULL;
	return NULL;
}

bool MoveTiledSprite::init(const char *$fileName , float $speed, float $angle , bool $isSpriteFrame){
	if(!CCSpriteBatchNode::initWithFile($fileName, kDefaultSpriteBatchCapacity)) return false;
	m_speed = $speed;
	float rad = $angle * M_PI / 180;
	m_dx = cosf(rad) * m_speed;
	m_dy = sinf(rad) * m_speed;
	m_isSpriteFrame = $isSpriteFrame;
	setVisibleSize(CCDirector::sharedDirector()->getVisibleSize());
	setTile();
	scheduleUpdate();
	return true;
}

//タイルをしきつめる
void MoveTiledSprite::setTile(){
	int count = 0;
	int col = 0;
	int row = 0;
	while(true){
		CCSprite* sprite = makeSprite();
		int tag = getSpriteTag(col, row);
		sprite->setTag(tag);
		if(m_spriteSize.equals(CCSizeZero)){
			m_spriteSize = sprite->getContentSize();
		}
		
		float x =  m_spriteSize.width * (col - 1) + m_spriteSize.width / 2;
		float y =  m_spriteSize.height * (row - 1) + m_spriteSize.height / 2;
		sprite->setPosition(ccp(x , y));
		this->addChild(sprite);

		//xをアレする
		col++;
		if(m_spriteSize.width * (col - 1) + m_spriteSize.width / 2 > m_size.width){
			if(m_spriteSize.height * (row - 1) + m_spriteSize.height / 2 > m_size.height){
				break;
			}
			col = -1;
			row++;
		}
		count++;
		if(count > 1000) break;
	}
}

//スプライトを作成する
CCSprite* MoveTiledSprite::makeSprite(){
	return m_isSpriteFrame ? CCSprite::createWithSpriteFrameName(m_tilename.c_str()) : CCSprite::create(m_tilename.c_str());
}

int MoveTiledSprite::getSpriteTag(int $x, int $y){
	return kTagSprite + 1000 * $y + $x;
}

MoveTiledSprite::TilePos MoveTiledSprite::getTilePos(int $tag){
	int x = ($tag - kTagSprite) % 1000;
	int y = ($tag - kTagSprite) / 1000;
	return TilePos(x , y);
}


void MoveTiledSprite::update(float $df){
	CCArray* ary = this->getChildren();
	CCObject* obj = NULL;
	if(ary->count() > 0){
		CCArray* array = CCArray::create();
		CCARRAY_FOREACH(ary, obj){
			array->addObject(obj);
		}
		if(array->count() > 0){
			CCARRAY_FOREACH(array, obj){
				if(CCSprite* node = dynamic_cast<CCSprite*>(obj)){
					moveSprite(node);
				}
			}
		}
		CC_SAFE_RELEASE(array);
		array = NULL;
	}
}

//移動＆はみでてたら削除したり新たに隣に追加したり
void MoveTiledSprite::moveSprite(cocos2d::CCSprite *node){
	//移動
	rectType type = typeOfSprite(node);
	node->setPosition(node->getPosition() + ccp(m_dx , m_dy));
	if(type == type_outer){
		node->removeFromParent();
	}else if(type == type_border){
		//新たに作成する
		makeAroundTile(node);
	}
}


//周りの部分を作成する
void MoveTiledSprite::makeAroundTile(cocos2d::CCSprite *$sprite){
	TilePos tilepos = getTilePos($sprite->getTag());
	CCPoint pos = $sprite->getPosition();
	CCSize size = $sprite->getContentSize();
	float left = pos.x - size.width / 2;
	float right = pos.x + size.width / 2;
	float top = pos.y + size.height / 2;
	float bottom = pos.y - size.height / 2;
	//上が開いてる場合上を作成
	if(m_dy < 0 && top <= m_size.height){
		TilePos tile = TilePos(tilepos);
		tile.add(0,-1);
		CCPoint $pos = pos + ccp(0 , size.height);
		makeTile(getSpriteTag(tile.x, tile.y) , $pos);
	}else if(m_dy >= 0 && bottom >= 0){
		TilePos tile = TilePos(tilepos);
		tile.add(0,1);
		CCPoint $pos = pos - ccp(0 , size.height);
		makeTile(getSpriteTag(tile.x, tile.y) , $pos);
	}
	
	if(m_dx >= 0 && left >= 0){
		TilePos tile = TilePos(tilepos);
		tile.add(-1,0);
		CCPoint $pos = pos - ccp(size.width , 0);
		makeTile(getSpriteTag(tile.x, tile.y) , $pos);
	}else if(m_dx < 0 && right <= m_size.width){
		TilePos tile = TilePos(tilepos);
		tile.add(1,0);
		CCPoint $pos = pos + ccp(size.width , 0);
		int tag = getSpriteTag(tile.x, tile.y);
		makeTile(tag, $pos);
	}
}

//タイルを作成(もし存在する場合は何もしない)
void MoveTiledSprite::makeTile(int tag, const cocos2d::CCPoint &$pos){
	if(this->getChildByTag(tag)){
		return;
	}
	CCSprite* sprite = makeSprite();
	sprite->setTag(tag);
	sprite->setPosition($pos);
	this->addChild(sprite);
}



MoveTiledSprite::rectType MoveTiledSprite::typeOfSprite(cocos2d::CCNode* node){
	CCPoint pos = node->getPosition();
	CCSize size = node->getContentSize();
	float left = pos.x - size.width / 2;
	float right = pos.x + size.width / 2;
	float top = pos.y + size.height / 2;
	float bottom = pos.y - size.height / 2;
	//中に全部入ってる
	if(left > 0 &&  right < m_size.width && bottom > 0  && top < m_size.height){
		return type_inner;
	}
	
	//外に全部出てる
	if((right < 0 || left > m_size.width || top < 0 || bottom > m_size.height)){
		return type_outer;
	}
	
	if((left < 0 && right >= 0) || (left <= m_size.width && right > m_size.width) ||
	   (bottom < 0 && top >= 0 ) || (bottom <= m_size.width && top > m_size.width )){
		return type_border;
	}
	return type_border;
}

