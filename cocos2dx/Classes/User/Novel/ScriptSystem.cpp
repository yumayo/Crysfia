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

#include "ScriptHuman.h"
#include "ScriptBackground.h"
#include "ScriptName.h"
#include "ScriptStill.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

namespace User
{
    size_t ScriptSystem::novelIndex = 0;

    ScriptSystem::ScriptSystem( cocos2d::Layer* layer )
        : ScriptBase( layer )
    {
        REGIST_SCRIPT( u8"SETUP", ScriptSystem::SETUP );
        REGIST_SCRIPT( u8"l", ScriptSystem::l );
        REGIST_SCRIPT( u8"select", ScriptSystem::select );
        REGIST_SCRIPT( u8"stop", ScriptSystem::stop );
        REGIST_SCRIPT( u8"bgm", ScriptSystem::bgm );
        REGIST_SCRIPT( u8"se", ScriptSystem::se );
        REGIST_SCRIPT( u8"name", ScriptSystem::name );
        REGIST_SCRIPT( u8"human", ScriptSystem::human );
        REGIST_SCRIPT( u8"background", ScriptSystem::background );
        REGIST_SCRIPT( u8"still", ScriptSystem::still );
        REGIST_SCRIPT( u8"novelon", ScriptSystem::novelon );
        REGIST_SCRIPT( u8"noveloff", ScriptSystem::noveloff );
    }
    ScriptSystem::~ScriptSystem( )
    {

    }
    void ScriptSystem::SETUP( ArgumentList const& args )
    {
        auto systemLayer = dynamic_cast<SystemLayer*>( layer );
        humanLayer = systemLayer->getLayer<HumanLayer>( );
        backgroundLayer = systemLayer->getLayer<BackgroundLayer>( );
        nameLayer = systemLayer->getLayer<NameLayer>( );
        novelLayer = systemLayer->getLayer<NovelLayer>( );
        selectLayer = systemLayer->getLayer<SelectLayer>( );
        stillLayer = systemLayer->getLayer<StillLayer>( );
    }
    void ScriptSystem::l( ArgumentList const& args )
    {
        novelIndex = lineSize;
    }
    void ScriptSystem::select( ArgumentList const & args )
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
    void ScriptSystem::stop( ArgumentList const & args )
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
    void ScriptSystem::novelon( ArgumentList const& args )
    {
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->on( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->on( );
    }
    void ScriptSystem::noveloff( ArgumentList const& args )
    {
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->off( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->off( );
    }
    void ScriptSystem::name( ArgumentList const & args )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string variable = args[0];
            std::string humanName = variable;
            auto pos = variable.find( u8"–¼‘O" );
            if ( pos != std::string::npos ) humanName = variable.substr( pos + std::string( u8"–¼‘O" ).size( ) );

            auto script = new ScriptName( nameLayer, humanName, u8"F910MinchoW3.otf" );
            ScriptStaticData::addData( std::make_pair( variable, std::unique_ptr<ScriptBase>( script ) ) );
        }
        break;
        case 2:
        {
            auto script = new ScriptName( nameLayer, args[1], u8"F910MinchoW3.otf" );
            ScriptStaticData::addData( std::make_pair( args[0], std::unique_ptr<ScriptBase>( script ) ) );
        }
        break;
        default:
            break;
        }
    }
    void ScriptSystem::background( ArgumentList const & args )
    {
        if ( 1 == args.size( ) )
        {
            std::string variable = args[0];
            auto script = new ScriptBackground( backgroundLayer, variable + u8".png" );
            ScriptStaticData::addData( std::make_pair( variable, std::unique_ptr<ScriptBase>( script ) ) );
        }
    }
    void ScriptSystem::bgm( ArgumentList const & args )
    {

    }
    void ScriptSystem::se( ArgumentList const & args )
    {

    }
    void ScriptSystem::human( ArgumentList const & args )
    {
        if ( 1 == args.size( ) )
        {
            std::string variable = args[0];
            auto script = new ScriptHuman( humanLayer, variable + u8".png" );
            ScriptStaticData::addData( std::make_pair( variable, std::unique_ptr<ScriptBase>( script ) ) );
        }
    }
    void ScriptSystem::still( ArgumentList const & args )
    {
        if ( 1 == args.size( ) )
        {
            std::string variable = args[0];
            auto script = new ScriptStill( stillLayer, variable + u8".png" );
            ScriptStaticData::addData( std::make_pair( variable, std::unique_ptr<ScriptBase>( script ) ) );
        }
    }
}
