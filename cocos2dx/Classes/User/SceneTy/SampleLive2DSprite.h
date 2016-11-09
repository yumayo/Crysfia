/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#ifndef __sampleCocos2dx__SampleLive2DSprite__
#define __sampleCocos2dx__SampleLive2DSprite__

#include "cocos2d.h"
#include "2d/CCSprite.h"
#include <vector>
#include "Live2DModelOpenGL.h"


class SampleLive2DSprite :public cocos2d::DrawNode {

    live2d::Live2DModelOpenGL* live2DModel;

public:
    SampleLive2DSprite( );
    virtual ~SampleLive2DSprite( );

    virtual bool init( );
    virtual void draw( cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags ) override;
    void onDraw( const cocos2d::Mat4 &transform, uint32_t flags );
    static SampleLive2DSprite* createDrawNode( );
protected:
    cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__sampleCocos2dx__SampleLive2DSprite__) */
