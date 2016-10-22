#ifndef __ScriptTestLayer__
#define __ScriptTestLayer__

#include "cocos2d.h"

#include "../LayerBase.h"

#include "TextData.h"
#include "TextLabels.h"
#include "TextScriptReader.h"
#include "TextChank.h"

namespace User
{
    class ScriptTestLayer : public LayerBase
    {
    public:
        CREATE_FUNC( ScriptTestLayer );
        virtual bool init( )override;
        virtual void setup( )override;
        virtual void cleanup( )override;
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
        User::TextScriptReader textReader;
        User::TextChank textChank;
        User::TextLabels textLabels;
    };
}


#endif // __ScriptTestLayer__
