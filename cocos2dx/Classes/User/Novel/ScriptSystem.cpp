#include "ScriptSystem.h"

#include "ScriptStaticData.h"
#include "OptionalValues.h"

#include "SystemLayer.h"
#include "NameLayer.h"
#include "BackgroundLayer.h"
#include "HumanLayer.h"
#include "NovelLayer.h"
#include "SelectLayer.h"
#include "StillLayer.h"
#include "HeartLayer.h"
#include "Live2dLayer.h"

#include "ScriptHuman.h"
#include "ScriptBackground.h"
#include "ScriptName.h"
#include "ScriptStill.h"
#include "ScriptHeart.h"
#include "ScriptLive2d.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

namespace User
{
    size_t ScriptSystem::novelIndex = 0;
    bool ScriptSystem::isShowNovel = true;

    ScriptSystem::ScriptSystem( cocos2d::Layer* layer )
        : ScriptBase( layer )
    {
        REGIST_FUNC( ScriptSystem, l );
        REGIST_FUNC( ScriptSystem, select );
        REGIST_FUNC( ScriptSystem, stop );
        REGIST_FUNC( ScriptSystem, heart );
        REGIST_FUNC( ScriptSystem, bgm );
        REGIST_FUNC( ScriptSystem, se );
        REGIST_FUNC( ScriptSystem, name );
        REGIST_FUNC( ScriptSystem, human );
        REGIST_FUNC( ScriptSystem, background );
        REGIST_FUNC( ScriptSystem, still );
        REGIST_FUNC( ScriptSystem, live2d );
        REGIST_FUNC( ScriptSystem, novelon );
        REGIST_FUNC( ScriptSystem, noveloff );
        REGIST_FUNC( ScriptSystem, novelswitch );
    }
    ScriptSystem::~ScriptSystem( )
    {

    }
    void ScriptSystem::setup( )
    {
        ScriptStaticData::setup( );

        novelIndex = 0;
        isShowNovel = true;

        auto systemLayer = dynamic_cast<SystemLayer*>( layer );
        humanLayer = systemLayer->getLayer<HumanLayer>( );
        backgroundLayer = systemLayer->getLayer<BackgroundLayer>( );
        nameLayer = systemLayer->getLayer<NameLayer>( );
        novelLayer = systemLayer->getLayer<NovelLayer>( );
        selectLayer = systemLayer->getLayer<SelectLayer>( );
        stillLayer = systemLayer->getLayer<StillLayer>( );
        heartLayer = systemLayer->getLayer<HeartLayer>( );
        live2dLayer = systemLayer->getLayer<Live2dLayer>( );
    }
    SCRIPT( ScriptSystem::l )
    {
        novelIndex = lineSize;
    }
    SCRIPT( ScriptSystem::select )
    {
        l( args );

        auto novel = dynamic_cast<NovelLayer*>( novelLayer );
        novel->systemStop.on( );

        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );


        Vector<MenuItem*> buttons;
        for ( size_t i = 0; i < args.size( ); ++i )
        {
            auto label = Label::createWithTTF( args[i], OptionalValues::fontName, OptionalValues::fontSize );
            auto item = MenuItemLabel::create( label, [ = ] ( Ref* pSender )
            {
                novel->select( args[i] );
                novel->click( );
            } );
            buttons.pushBack( item );
        }

        if ( auto menu = Menu::createWithArray( buttons ) )
        {
            menu->setPosition( origin + visibleSize * 0.5F );
            menu->alignItemsVerticallyWithPadding( OptionalValues::fontSize );
            menu->setName( u8"select" );
            selectLayer->addChild( menu );
        }
    }
    SCRIPT( ScriptSystem::stop )
    {
        auto novel = dynamic_cast<NovelLayer*>( novelLayer );
        switch ( args.size( ) )
        {
        case 0:
            novel->setDelayTime( 1.0 );
            break;
        case 1:
            novel->setDelayTime( std::stod( args[0] ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::novelon )
    {
        isShowNovel = true;
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->on( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->on( );
    }
    SCRIPT( ScriptSystem::noveloff )
    {
        isShowNovel = false;
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->off( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->off( );
    }
    SCRIPT( ScriptSystem::novelswitch )
    {
        if ( isShowNovel )
        {
            noveloff( args );
        }
        else
        {
            novelon( args );
        }
    }
    SCRIPT( ScriptSystem::name )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string variable = args[0];
            std::string humanName = variable;
            auto pos = variable.find( u8"���O" );
            if ( pos != std::string::npos ) humanName = variable.substr( pos + std::string( u8"���O" ).size( ) );

            REGIST_VARIABLE( variable, new ScriptName( nameLayer, humanName, u8"F910MinchoW3.otf" ) );
        }
        break;
        case 2:
        {
            REGIST_VARIABLE( args[0], new ScriptName( nameLayer, args[1], u8"F910MinchoW3.otf" ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::background )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptBackground( backgroundLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::bgm )
    {

    }
    SCRIPT( ScriptSystem::se )
    {

    }
    SCRIPT( ScriptSystem::human )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptHuman( stillLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::still )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptStill( stillLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::heart )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptHeart( heartLayer ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::live2d )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto var = args[0];
            auto dir = u8"res/live2d/" + var + u8"/";
            auto json = var + u8".model.json";
            REGIST_VARIABLE( var, new ScriptLive2d( live2dLayer, dir, json ) );
        }
        break;
        default:
            break;
        }
    }
}
