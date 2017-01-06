#include "ScriptLive2d.h"

#include "../Live2d/LAppView.h"
#include "../Live2d/LAppLive2DManager.h"

#include "ScriptStaticData.h"

#include "../Live2d/LAppDefine.h"

USING_NS_CC;

namespace User
{
    ScriptLive2d::ScriptLive2d( cocos2d::Layer* layer, std::string model, std::string dir )
        : ScriptBase( layer )
    {
        REGIST_FUNC( ScriptLive2d, in );
        REGIST_FUNC( ScriptLive2d, out );

        REGIST_FUNC_NAME( ScriptLive2d, normal, u8"•’Ê" );
        REGIST_FUNC_NAME( ScriptLive2d, rejoice, u8"Šì‚Ô" );
        REGIST_FUNC_NAME( ScriptLive2d, sorrow, u8"‹ƒ‚­" );
        REGIST_FUNC_NAME( ScriptLive2d, getSurprise, u8"‹Á‚­" );
        REGIST_FUNC_NAME( ScriptLive2d, getAngry, u8"“{‚é" );

        REGIST_FUNC( ScriptLive2d, touchon );
        REGIST_FUNC( ScriptLive2d, touchoff );

        auto manager = LAppLive2DManager::getInstance( );
        manager->createModel( dir, model + u8".model.json" );
        LAppLive2DManager::getInstance( )->enableModel( false );

        node = LAppView::createDrawNode( );
        node->setTag( (int)Tag::Live2d );
        layer->addChild( node );
    }
    ScriptLive2d::~ScriptLive2d( )
    {

    }
    SCRIPT( ScriptLive2d::in )
    {
        LAppLive2DManager::getInstance( )->enableModel( true );
    }
    SCRIPT( ScriptLive2d::out )
    {
        LAppLive2DManager::getInstance( )->enableModel( false );
    }
    SCRIPT( ScriptLive2d::normal )
    {
        auto manager = LAppLive2DManager::getInstance( );
        manager->setExpression( u8"•’Ê" );
        manager->setMotion( MOTION_GROUP_TAP_BODY, 7 );
    }
    SCRIPT( ScriptLive2d::rejoice )
    {
        auto manager = LAppLive2DManager::getInstance( );
        manager->setExpression( u8"ƒjƒRƒjƒR" );
        manager->setMotion( MOTION_GROUP_TAP_BODY, 8 );
    }
    SCRIPT( ScriptLive2d::sorrow )
    {
        auto manager = LAppLive2DManager::getInstance( );
        manager->setExpression( u8"‚µ‚å‚ñ‚Ú‚è" );
        manager->setMotion( MOTION_GROUP_TAP_BODY, 5 );
    }
    SCRIPT( ScriptLive2d::getSurprise )
    {
        auto manager = LAppLive2DManager::getInstance( );
        manager->setExpression( u8"‹Á‚­" );
        manager->setMotion( MOTION_GROUP_TAP_BODY, 0 );
    }
    SCRIPT( ScriptLive2d::getAngry )
    {
        auto manager = LAppLive2DManager::getInstance( );
        manager->setExpression( u8"“{‚é" );
        manager->setMotion( MOTION_GROUP_TAP_BODY, 4 );
    }
    SCRIPT( ScriptLive2d::touchon )
    {
        node->resume( );
    }
    SCRIPT( ScriptLive2d::touchoff )
    {
        node->pause( );
    }
}
