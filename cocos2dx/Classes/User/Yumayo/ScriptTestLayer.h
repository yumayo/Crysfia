#ifndef __ScriptTestLayer__
#define __ScriptTestLayer__

#include "cocos2d.h"

#include "../LayerBase.h"

#include "TextData.h"
#include "TextLabels.h"
#include "ScriptReader.h"
#include "TextChank.h"

class ScriptTestLayer : public cocos2d::Layer
{
public:
    virtual bool init( )override;
    virtual void cleanup( )override;

    // implement the "static create()" method manually
    CREATE_FUNC( ScriptTestLayer );
public:
    void windowDefineUpdate( );
    void update( float delta )override;
private:
    cocos2d::EventListenerMouse* mouseEvent;
    std::vector<cocos2d::Sprite*> sprities = std::vector<cocos2d::Sprite*>( 5 );
    cocos2d::Vec2 mousePosition;
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;

    User::TextData textData;
    User::ScriptReader reader;
    User::TextChank textChank;
    User::TextLabels textLabels;
};

#endif // __ScriptTestLayer__
