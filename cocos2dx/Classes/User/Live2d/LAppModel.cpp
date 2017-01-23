/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppModel.h"


#include "LAppDefine.h"

#include "ModelSettingJson.h"

#include "SimpleAudioEngine.h"
#include "platform/CCImage.h"

using namespace CocosDenshion;

using namespace std;
using namespace live2d;
using namespace live2d::framework;
USING_NS_CC;


LAppModel::LAppModel( )
    :L2DBaseModel( ), modelSetting( nullptr )
{

    if ( LAppDefine::DEBUG_LOG )
    {
        debugMode = true;
    }
}


LAppModel::~LAppModel( void )
{
    if ( LAppDefine::DEBUG_LOG )log( "delete model" );

    for ( int i = 0; i < modelSetting->getMotionGroupNum( ); i++ )
    {
        std::string group = modelSetting->getMotionGroupName( i );
        releaseMotionGroup( group );
    }
    delete modelSetting;
}


void LAppModel::load( std::string dir, std::string fileName )
{
    modelHomeDir = dir;

    if ( LAppDefine::DEBUG_LOG )log( "create model : %s", fileName.c_str( ) );


    ssize_t size;
    string path = fileName;
    path = dir + path;
    unsigned char* data = CCFileUtils::getInstance( )->getFileData( path.c_str( ), "rb", &size );

    ModelSetting* setting = new ModelSettingJson( (const char*)data, size );
    free( data );
    init( setting );
}


void LAppModel::init( ModelSetting* setting )
{
    updating = true;
    initialized = false;

    modelSetting = setting;

    if ( strcmp( modelSetting->getModelFile( ).c_str( ), "" ) != 0 )
    {
        string path = modelSetting->getModelFile( );
        path = modelHomeDir + path;
        loadModelData( path.c_str( ) );

        int len = modelSetting->getTextureNum( );


        for ( int i = 0; i < len; i++ )
        {
            string texturePath = modelSetting->getTextureFile( i );
            texturePath = modelHomeDir + texturePath;
            loadTexture( i, texturePath.c_str( ) );
        }
    }

    if ( modelSetting->getExpressionNum( ) > 0 )
    {
        int len = modelSetting->getExpressionNum( );
        for ( int i = 0; i < len; i++ )
        {
            string name = modelSetting->getExpressionName( i );
            string file = modelSetting->getExpressionFile( i );
            file = modelHomeDir + file;
            loadExpression( name.c_str( ), file.c_str( ) );
        }
    }

    if ( !modelSetting->getPhysicsFile( ).empty( ) )
    {
        string path = modelSetting->getPhysicsFile( );
        path = modelHomeDir + path;
        loadPhysics( path.c_str( ) );
    }

    if ( !modelSetting->getPoseFile( ).empty( ) )
    {
        string path = modelSetting->getPoseFile( );
        path = modelHomeDir + path;
        loadPose( path.c_str( ) );
    }

    map<string, float> layout;
    modelSetting->getLayout( layout );
    modelMatrix->setupLayout( layout );


    for ( int i = 0; i < modelSetting->getInitParamNum( ); i++ )
    {
        live2DModel->setParamFloat( modelSetting->getInitParamID( i ).c_str( ), modelSetting->getInitParamValue( i ) );
    }

    for ( int i = 0; i < modelSetting->getInitPartsVisibleNum( ); i++ )
    {
        live2DModel->setPartsOpacity( modelSetting->getInitPartsVisibleID( i ).c_str( ), modelSetting->getInitPartsVisibleValue( i ) );
    }

    live2DModel->saveParam( );
    live2DModel->setPremultipliedAlpha( true );

    for ( int i = 0; i < modelSetting->getMotionGroupNum( ); i++ )
    {
        std::string group = modelSetting->getMotionGroupName( i );
        preloadMotionGroup( group );
    }

    mainMotionMgr->stopAllMotions( );



    updating = false;
    initialized = true;
}


void LAppModel::preloadMotionGroup( std::string group )
{
    int len = modelSetting->getMotionNum( group );
    for ( int i = 0; i < len; i++ )
    {
        std::stringstream ss;

        ss << group << "_" << i;

        string name = ss.str( );
        string path = modelSetting->getMotionFile( group, i );
        path = modelHomeDir + path;

        if ( LAppDefine::DEBUG_LOG )log( "load motion name:%s ", name.c_str( ) );

        loadMotion( name.c_str( ), path.c_str( ) );

        std::string voice = modelSetting->getMotionSound( group, i );
        if ( !voice.empty( ) )
        {
            string path = voice;
            path = modelHomeDir + path;


            SimpleAudioEngine::getInstance( )->preloadEffect( path.c_str( ) );
        }
    }
}


void LAppModel::releaseMotionGroup( std::string group )
{
    int len = modelSetting->getMotionNum( group );
    for ( int i = 0; i < len; i++ )
    {
        std::string voice = modelSetting->getMotionSound( group, i );
        if ( !voice.empty( ) )
        {
            string path = voice;
            path = modelHomeDir + path;

            SimpleAudioEngine::getInstance( )->unloadEffect( path.c_str( ) );
        }
    }
}


void LAppModel::update( )
{
    dragMgr->update( );
    dragX = dragMgr->getX( );
    dragY = dragMgr->getY( );

    live2DModel->loadParam( );
    if ( mainMotionMgr->isFinished( ) )
    {
        startRandomMotion( MOTION_GROUP_IDLE, PRIORITY_IDLE );
    }
    else
    {
        mainMotionMgr->updateParam( live2DModel );
    }
    live2DModel->saveParam( );


    if ( expressionMgr != nullptr )expressionMgr->updateParam( live2DModel );

    live2DModel->addToParamFloat( PARAM_ANGLE_X, dragX * 30 );
    live2DModel->addToParamFloat( PARAM_ANGLE_Y, dragY * 30 );
    live2DModel->addToParamFloat( PARAM_ANGLE_Z, ( dragX * dragY ) * -30 );

    live2DModel->addToParamFloat( PARAM_BODY_ANGLE_X, dragX * 10 );

    live2DModel->addToParamFloat( PARAM_EYE_BALL_X, dragX );
    live2DModel->addToParamFloat( PARAM_EYE_BALL_Y, dragY );

    long timeMSec = UtSystem::getUserTimeMSec( ) - startTimeMSec;
    double t = ( timeMSec / 1000.0 ) * 2 * 3.14159;

    live2DModel->addToParamFloat( PARAM_ANGLE_X, (float)( 15 * sin( t / 6.5345 ) ), 0.5f );
    live2DModel->addToParamFloat( PARAM_ANGLE_Y, (float)( 8 * sin( t / 3.5345 ) ), 0.5f );
    live2DModel->addToParamFloat( PARAM_ANGLE_Z, (float)( 10 * sin( t / 5.5345 ) ), 0.5f );
    live2DModel->addToParamFloat( PARAM_BODY_ANGLE_X, (float)( 4 * sin( t / 15.5345 ) ), 0.5f );
    live2DModel->setParamFloat( PARAM_BREATH, (float)( 0.5f + 0.5f * sin( t / 3.2345 ) ), 1 );


    if ( physics != nullptr )physics->updateParam( live2DModel );

    if ( lipSync )
    {
        float value = 0;
        live2DModel->setParamFloat( PARAM_MOUTH_OPEN_Y, value, 0.8f );
    }

    if ( pose != nullptr )pose->updateParam( live2DModel );

    live2DModel->update( );

}


int LAppModel::startMotion( std::string group, int no, int priority )
{
    if ( priority == PRIORITY_FORCE )
    {
        mainMotionMgr->setReservePriority( priority );
    }
    else if ( !mainMotionMgr->reserveMotion( priority ) )
    {
        if ( LAppDefine::DEBUG_LOG )log( "can't start motion.\n" );
        return -1;
    }

    std::string fileName = modelSetting->getMotionFile( group, no );
    std::stringstream ss;

    ss << group << "_" << no;

    string name = ss.str( );
    AMotion* motion = motions[name.c_str( )];
    bool autoDelete = false;
    if ( motion == nullptr )
    {
        string path = fileName;
        path = modelHomeDir + path;
        motion = loadMotion( nullptr, path.c_str( ) );

        autoDelete = true;
    }

    motion->setFadeIn( modelSetting->getMotionFadeIn( group, no ) );
    motion->setFadeOut( modelSetting->getMotionFadeOut( group, no ) );

    if ( LAppDefine::DEBUG_LOG )log( "start motion ( %s : %d )", group.c_str( ), no );

    std::string voice = modelSetting->getMotionSound( group, no );
    if ( !voice.empty( ) )
    {
        string path = voice;

        path = modelHomeDir + path;

        SimpleAudioEngine::getInstance( )->playEffect( path.c_str( ) );
    }


    return mainMotionMgr->startMotionPrio( motion, autoDelete, priority );
}


int LAppModel::startRandomMotion( std::string name, int priority )
{
    if ( modelSetting->getMotionNum( name ) == 0 )return -1;
    int no = rand( ) % modelSetting->getMotionNum( name );

    return startMotion( name, no, priority );
}


void LAppModel::draw( )
{
    if ( live2DModel == nullptr )return;

    live2DModel->draw( );
}


void LAppModel::draw( live2d::framework::L2DMatrix44& matrix )
{
    if ( live2DModel == nullptr )return;

    float mvp[16];
    L2DMatrix44::mul( matrix.getArray( ), modelMatrix->getArray( ), mvp );
    ( (Live2DModelOpenGL*)live2DModel )->setMatrix( mvp );
    draw( );
}


bool LAppModel::hitTest( std::string pid, float testX, float testY )
{
    if ( alpha < 1 )return false;
    int len = modelSetting->getHitAreasNum( );

    for ( int i = 0; i < len; i++ )
    {
        if ( modelSetting->getHitAreaName( i ) == pid )
        {
            std::string drawID = modelSetting->getHitAreaID( i );
            return hitTestSimple( drawID.c_str( ), testX, testY );
        }
    }
    return false;
}


void LAppModel::setExpression( std::string expressionID )
{
    AMotion* motion = expressions[expressionID];
    if ( LAppDefine::DEBUG_LOG )log( "expression[%s]", expressionID.c_str( ) );
    if ( motion != nullptr )
    {
        expressionMgr->startMotion( motion, false );
    }
    else
    {
        if ( LAppDefine::DEBUG_LOG )log( "expression[%s] is nullptr ", expressionID.c_str( ) );
    }
}


void LAppModel::setRandomExpression( )
{
    int no = rand( ) % expressions.size( );
    map<string, AMotion* >::const_iterator map_ite;
    int i = 0;
    for ( map_ite = expressions.begin( ); map_ite != expressions.end( ); map_ite++ )
    {
        if ( i == no )
        {
            string name = ( *map_ite ).first;
            setExpression( name.c_str( ) );
            return;
        }
        i++;
    }
}