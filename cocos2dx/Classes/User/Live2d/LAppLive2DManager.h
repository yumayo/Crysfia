/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once
#include <vector>
#include "LAppDefine.h"
#include "L2DTargetPoint.h"
#include "L2DMatrix44.h"
#include "cocos2d.h"

class LAppModel;

class LAppLive2DManager
{
private:
    LAppModel* work = nullptr;
    LAppModel* model = nullptr;
    live2d::framework::L2DMatrix44* viewMatrix = nullptr;
public:
    static LAppLive2DManager* getInstance( );
    static void releaseInstance( );

#ifdef L2D_TARGET_ANDROID_ES2
    void reinit( );
#endif
    void onDrag( float x, float y );
    void onTap( float x, float y );
    void onUpdate( );

    void setViewMatrix( live2d::framework::L2DMatrix44* m ) { viewMatrix = m; }

    void releaseModel( );
    LAppModel* getModel() { return model; }

    void setExpression( std::string name );
    void setMotion( std::string name, int no );
    void createModel( std::string dirPath, std::string jsonPath );
    void enableModel( bool enable );
    // モデルが存在するなら true
    // 存在しないなら false
    bool isExist( );
private:
    LAppLive2DManager( );
    virtual ~LAppLive2DManager( );
};
