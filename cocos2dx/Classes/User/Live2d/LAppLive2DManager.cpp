/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppLive2DManager.h"


//Live2D Application
#include "LAppModel.h"
#include "PlatformManager.h"

#include "L2DStandardID.h"
#include "Live2DFramework.h"

#include "graphics/DrawProfileCocos2D.h"

#ifdef L2D_TARGET_ANDROID_ES2
    //android向けのシェーダ設定のために読み込み
#include "graphics/DrawParam_OpenGLES2.h"
#endif

USING_NS_CC;

using namespace live2d;
using namespace live2d::framework;

static LAppLive2DManager* instance = nullptr;



LAppLive2DManager* LAppLive2DManager::getInstance( )
{
    if ( instance == nullptr )
    {
        instance = new LAppLive2DManager( );
    }

    return instance;
}


void LAppLive2DManager::releaseInstance( )
{
    if ( instance )
    {
        delete instance;
        auto framework = live2d::framework::Live2DFramework::getPlatformManager( );
        delete framework;
        framework = nullptr;
    }

    instance = nullptr;
}


LAppLive2DManager::LAppLive2DManager( )
{
    if ( LAppDefine::DEBUG_LOG )
    {
        log( "==============================================" );
        log( "         BEGIN Live2D SDK Sample App1" );
        log( "==============================================" );
    }

    // 以下の命令でメモリリークの検査を実施（_DEBUGモードのみ）
    // Live2D::dispose()時に、Live2Dの管理するメモリでリークが発生していた場合にダンプする
    // リークしている場合は、MEMORY_DEBUG_MEMORY_INFO_ALLでより詳細な情報をダンプします
    // 検査用のデータはglobal new演算子を使います
    //UtDebug::addMemoryDebugFlags( live2d::UtDebug::MEMORY_DEBUG_MEMORY_INFO_COUNT ) ;

    // Initialize Live2D
    //Live2D::init( &myAllocator );
    Live2D::init( );

#ifdef L2D_TARGET_ANDROID_ES2
    char *exts = (char*)glGetString( GL_EXTENSIONS );
    if ( strstr( exts, "GL_NV_shader_framebuffer_fetch " ) ) {
        live2d::DrawParam_OpenGLES2::setExtShaderMode( true, true );
    }
#endif

    Live2DFramework::setPlatformManager( new PlatformManager( ) );
}


LAppLive2DManager::~LAppLive2DManager( )
{
    if ( LAppDefine::DEBUG_LOG )
    {
        log( "==============================================" );
        log( "         END Live2D SDK Sample App1" );
        log( "==============================================" );
    }

    releaseModel( );
    Live2D::dispose( );
}


void LAppLive2DManager::releaseModel( )
{
    delete model;
    model = nullptr;
    work = nullptr;
}

#ifdef L2D_TARGET_ANDROID_ES2
void LAppLive2DManager::reinit( )
{
    live2d::DrawParam_OpenGLES2::reloadShader( );
}
#endif

void LAppLive2DManager::onDrag( float x, float y )
{
    if ( !work ) return;

    work->setDrag( x, y );
}


void LAppLive2DManager::onTap( float x, float y )
{
    if ( LAppDefine::DEBUG_LOG )log( "tapEvent" );

    if ( !work ) return;

    if ( work->hitTest( HIT_AREA_NAME_HEAD, x, y ) )
    {
        if ( LAppDefine::DEBUG_LOG )log( "face" );
        work->setRandomExpression( );
    }
    else if ( work->hitTest( HIT_AREA_NAME_BODY, x, y ) )
    {
        if ( LAppDefine::DEBUG_LOG )log( "body" );
        work->startRandomMotion( MOTION_GROUP_TAP_BODY, PRIORITY_NORMAL );
    }
}

void LAppLive2DManager::onUpdate( )
{
    if ( !work ) return;

    live2d::DrawProfileCocos2D::preDraw( );

    L2DMatrix44 projection;
    Director* director = Director::getInstance( );
    Size window = director->getWinSize( );
    projection.scale( 1, window.width / window.height );

    if ( viewMatrix ) projection.append( viewMatrix );

    work->update( );
    work->draw( projection );

    live2d::DrawProfileCocos2D::postDraw( );
}


void LAppLive2DManager::setExpression( std::string name )
{
    if ( !work ) return;
    work->setExpression( name );
}

void LAppLive2DManager::setMotion( std::string name, int no )
{
    if ( !work ) return;
    work->startMotion( name, no, PRIORITY_NORMAL );
}

void LAppLive2DManager::createModel( std::string dirPath, std::string jsonPath )
{
    releaseModel( );
    model = new LAppModel( );
    model->load( dirPath.c_str( ), jsonPath.c_str( ) );
    work = model;
}

void LAppLive2DManager::enableModel( bool enable )
{
    if ( enable )
    {
        work = model;
    }
    else
    {
        
        work = nullptr;
    }
}

bool LAppLive2DManager::isExist( )
{
    return model != nullptr;
}
