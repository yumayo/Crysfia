/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include "cocos2d.h"


//Live2D Framework
#include "L2DBaseModel.h"
#include "L2DTargetPoint.h"
#include "L2DStandardID.h"

//Live2D Lib
#include "Live2DModelOpenGL.h"

//utils
#include "ModelSetting.h"


class LAppModel : public live2d::framework::L2DBaseModel
{
private:
    ModelSetting* modelSetting;
    std::string modelHomeDir;

public:
    LAppModel( );
    virtual ~LAppModel( void );
    //Initialize
    void init( ModelSetting* setting );

    //Load
    void load( std::string dir, std::string path );
    void preloadMotionGroup( std::string name );
    void releaseMotionGroup( std::string name );

    //Update
    void update( );
    void draw( );
    void draw( live2d::framework::L2DMatrix44& matrix );
    void setViewMatrix( float matrix[16] );

    // 全てのモーションデータを設定する。
    int startMotion( std::string group, int no, int priority );
    int startRandomMotion( std::string name, int priority );

    // 表情のアニメーションデータを設定する。
    // 上のstartMotionと競合はしない。
    // 一緒のフレームでやっても特に破綻したりはしない。
    void setExpression( std::string name );
    void setRandomExpression( );

    //Other
    virtual bool hitTest( std::string pid, float testX, float testY );
};



