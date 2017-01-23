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
#include "ItemLayer.h"
#include "VoiceLayer.h"
#include "FlickFunctionLayer.h"

#include "ScriptHuman.h"
#include "ScriptBackground.h"
#include "ScriptName.h"
#include "ScriptStill.h"
#include "ScriptHeart.h"
#include "ScriptLive2d.h"
#include "ScriptVoice.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "../../Lib/Utilitys.h"
#include "../../Lib/AudioManager.h"

#include "../SceneManager.h"

#include "../System/DataSettings.h"

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
        REGIST_FUNC( ScriptSystem, heartup );
        REGIST_FUNC( ScriptSystem, heartdown );
        REGIST_FUNC( ScriptSystem, still );
        REGIST_FUNC( ScriptSystem, live2d );
        REGIST_FUNC( ScriptSystem, voice );
        REGIST_FUNC( ScriptSystem, noveldisable );
        REGIST_FUNC( ScriptSystem, novelenable );
        REGIST_FUNC( ScriptSystem, novelon );
        REGIST_FUNC( ScriptSystem, noveloff );
        REGIST_FUNC( ScriptSystem, novelswitch );
        REGIST_FUNC( ScriptSystem, item );
        REGIST_FUNC( ScriptSystem, autosave );
        REGIST_FUNC( ScriptSystem, heartif );
        REGIST_FUNC( ScriptSystem, totitle );
        REGIST_FUNC( ScriptSystem, tobreeding );
        REGIST_FUNC( ScriptSystem, gameclear );
        REGIST_FUNC( ScriptSystem, remove );
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
        itemLayer = systemLayer->getLayer<ItemLayer>( );
        voiceLayer = systemLayer->getLayer<ItemLayer>( );
        flickFunctionLayer = systemLayer->getLayer<FlickFunctionLayer>( );
    }
    SCRIPT( ScriptSystem::l )
    {
        novelIndex = lineSize;
    }
    SCRIPT( ScriptSystem::select )
    {
        l( { } );

        auto novel = dynamic_cast<NovelLayer*>( novelLayer );
        novel->stop( );
        novel->systemStop.on( );

        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );

        Vector<MenuItem*> buttons;
        for ( size_t i = 0; i < args.size( ); ++i )
        {
            auto menuitem = MenuItemImage::create( u8"res/texture/system/select.base.png", u8"res/texture/system/select.select.png", [ = ] ( Ref* p )
            {
                if ( auto flick = dynamic_cast<FlickFunctionLayer*>( flickFunctionLayer ) )
                {
                    flick->end( );
                }

                novel->select( args[i] );
                novel->next( );
            } );

            auto scale = Director::getInstance( )->getContentScaleFactor( );
            menuitem->setScale( Lib::fitWidth( menuitem, visibleSize.width * 0.9 ) );
            auto label = Label::createWithTTF( args[i], OptionalValues::fontName, OptionalValues::fontSize );
            label->setColor( Color3B( 39, 39, 39 ) );
            label->setPosition( menuitem->getContentSize( ) * 0.5 );
            label->setScale( 1.0 / Lib::fitWidth( menuitem, visibleSize.width * 0.9 ) );
            menuitem->addChild( label );
            buttons.pushBack( menuitem );
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
    SCRIPT( ScriptSystem::noveldisable )
    {
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->noveldisable( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->noveldisable( );
    }
    SCRIPT( ScriptSystem::novelenable )
    {
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->novelenable( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->novelenable( );
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
    SCRIPT( ScriptSystem::item )
    {
        if ( auto ptr = dynamic_cast<ItemLayer*>( itemLayer ) )
        {
            ptr->make( args[0] );
        }
        l( { } );
    }
    SCRIPT( ScriptSystem::autosave )
    {
        utils::captureScreen( [ ] ( bool succeed, const std::string &filePath ) { }, "autosave.png" );
        stop( { u8"0.016F" } );
    }

    SCRIPT( ScriptSystem::heartup )
    {
        switch ( args.size( ) )
        {
        case 1:
        {

            auto heart = HeartGauge::create( )->make( );
            heart->scriptUpAction( args[0] );
            heartLayer->addChild( heart );
        }
        default:
            break;
        }
    }

    SCRIPT( ScriptSystem::heartdown )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto heart = HeartGauge::create( )->make( );
            heart->scriptDownAction( args[0] );
            heartLayer->addChild( heart );
        }
        default:
            break;
        }
    }

    SCRIPT( ScriptSystem::heartif )
    {
        // 引数が偶数の時のみ動作します。
        if ( ( args.size( ) & 0x1 ) == 0 )
        {
            // 奇数部分の数字が異常な値だったら例外を飛ばします。
            for ( int i = 0; i < args.size( ); i += 2 )
            {
                try
                {
                    StringUtil::string_value<int>( args[i] );
                }
                catch ( ... )
                {
                    throw( "heartifの引数が不正です。" );
                }
            }

            int heart = UserDefault::getInstance( )->getIntegerForKey( u8"親愛度" );
            for ( int i = 0; i < args.size( ); i += 2 )
            {
                int value = StringUtil::string_value<int>( args[i] );
                if ( heart <= value ) // 40 <= 50 ok -> return
                {
                    std::string next = args[i + 1];

                    auto novel = dynamic_cast<NovelLayer*>( novelLayer );
                    novel->stop( );
                    novel->systemStop.on( );

                    if ( auto flick = dynamic_cast<FlickFunctionLayer*>( flickFunctionLayer ) )
                    {
                        flick->end( );
                    }
                    novel->select( next );
                    novel->next( );
                    return;
                }
            }
        }
    }

    SCRIPT( ScriptSystem::totitle )
    {
        if ( auto p = dynamic_cast<NovelLayer*>( novelLayer ) )
        {
            p->next_scene = [ ] { SceneManager::createTitle( ); };
        }
    }
    SCRIPT( ScriptSystem::tobreeding )
    {
        if ( auto p = dynamic_cast<NovelLayer*>( novelLayer ) )
        {
            p->next_scene = [ ] { SceneManager::createBreeding( ); };
        }
    }

    SCRIPT( ScriptSystem::remove )
    {
        restart( );
    }

    SCRIPT( ScriptSystem::gameclear )
    {
        UserDefault::getInstance( )->setBoolForKey( u8"ゲームクリア", true );
    }

    SCRIPT( ScriptSystem::name )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::vector<std::string> names = { u8"名前", u8"n" };

            std::string variable = args[0];
            std::string humanName = variable;

            for ( auto& name : names )
            {
                auto pos = variable.find( name );
                if ( pos != std::string::npos )
                {
                    humanName = variable.substr( pos + std::string( name ).size( ) );
                    break;
                }
            }

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
        switch ( args.size( ) )
        {
        case 1:
        {
            auto audio = AudioManager::getInstance( );
            audio->playBgm( u8"res/bgm/" + args[0] + u8".mp3" );
        }
        break;
        case 2:
        {
            auto audio = AudioManager::getInstance( );
            audio->playBgm( u8"res/bgm/" + args[0] + u8".mp3", 0.0F, StringUtil::string_value<bool>( args[1] ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::se )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto audio = AudioManager::getInstance( );
            audio->playSe( u8"res/se/" + args[0] + u8".mp3" );
        }
        break;
        default:
            break;
        }
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
            auto index = UserDefault::getInstance( )->getIntegerForKey( u8"現在の服" );
            auto model = args[0];

            std::vector<std::string> names = 
            {
                u8"_d",//u8"ワンピース"
                u8"_d",//u8"ドレス",
                u8"_d",//u8"着ぐるみ",
                u8"_d",//u8"シスター服",
                u8"_s",//u8"セーラー服"
            };
            model += names[index];
            auto dir = u8"res/live2d/" + model + u8"/";
            REGIST_VARIABLE( args[0], new ScriptLive2d( live2dLayer, model, dir ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::voice )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto var = args[0];
            auto dir = u8"res/voice/" + var + u8"/";
            REGIST_VARIABLE( var, new ScriptVoice( voiceLayer, dir ) );
        }
        break;
        default:
            break;
        }
    }
}
