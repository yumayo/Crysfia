#include "LayerCity.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include <vector>
#include <functional>

#include "../Novel/ScriptHeart.h"

#include "../../Lib/Utility/Utilitys.h"

#include "../../Lib/Json/json.h"

#include "../System/DataSettings.h"

#include "LayerOption.h"

#include "SimpleAudioEngine.h"

#include "AudioEngine.h"

USING_NS_CC;

namespace User
{
    void LayerCityMark::setButtonEndCallBack( std::function<void( )>const& callback )
    {
        buttonEnd = callback;
    }
    void LayerCityMark::pasteMap( cocos2d::Sprite * map, ScenarioPointData const & data )
    {
        initData( data );

        auto pixel = map->getTexture( )->getContentSizeInPixels( );

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

        map->addChild( this );

        setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
        setScale( Lib::fitWidth( this, 64 * scale ), Lib::fitWidth( this, 64 * scale ) );
        if ( data.visit ) setEnabled( false );

        addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( auto parent = getParent( ) )
                {
                    auto pixel = map->getTexture( )->getContentSizeInPixels( );

                    auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

                    parent->removeChildByName( u8"ok.button" );

                    auto node = Node::create( );
                    node->setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
                    node->setName( u8"ok.button" );
                    parent->addChild( node );

                    const std::string dir = u8"res/texture/system/";
                    auto kuroe = Sprite::create( dir + "kuroeicon.png" );
                    auto kuroePixel = kuroe->getContentSize( ) / scale;
                    node->addChild( kuroe );

                    auto fitButton = Lib::fitWidth( kuroe, 64 * scale );
                    node->setScale( fitButton );

                    auto ok = ui::Button::create( dir + u8"ok.png" );
                    auto okPixel = ok->getContentSize( ) / scale;
                    node->addChild( ok );
                    ok->setPosition( Vec2( 0, -kuroePixel.height / 2 - okPixel.height / 2 ) * scale );
                    ok->addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
                    {
                        if ( type == ui::Widget::TouchEventType::ENDED )
                        {
                            if ( buttonEnd ) buttonEnd( );
                            map->pause( );
                        }
                    } );
                }
            }
        } );
    }

    void MainMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.main.png" );

        LayerCityMark::pasteMap( map, data );
    }

    void SubMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.sub.png" );

        LayerCityMark::pasteMap( map, data );

        setScale( getScale( ) * 0.5 );
    }

    Calendar* Calendar::make( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        setPosition( vo + vs );

        const std::string dir = u8"res/texture/system/";

        if ( auto calendar = Sprite::create( dir + "calendar.png" ) )
        {
            addChild( calendar );
            setContentSize( calendar->getContentSize( ) );
            calendar->setAnchorPoint( Vec2( 1, 1 ) );

            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

            auto pixel = calendar->getContentSize( ) / scale;

            day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );

            {
                auto font = Label::createWithTTF( StringUtils::toString( day ),
                                                  u8"res/fonts/HGRGE.TTC",
                                                  130 * scale );
                calendar->addChild( font );
                font->setAnchorPoint( Vec2( 0.5F, 0 ) );
                font->setPosition( Vec2( 90, ( pixel.height - 230 ) ) * scale );
                font->setColor( Color3B( 39, 39, 39 ) );
            }

            {
                auto font = Label::createWithTTF( u8"日目",
                                                  u8"res/fonts/HGRGE.TTC",
                                                  40 * scale );
                calendar->addChild( font );
                font->setPosition( Vec2( 203, ( pixel.height - 134 ) ) * scale );
                font->setColor( Color3B( 39, 39, 39 ) );
            }
        }

        return this;
    }

    CityMap* CityMap::make( std::string const& backgroundfile )
    {
        initWithFile( backgroundfile );

        auto size = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto targetSize = size;
        translate = origin + size / 2;
        auto backgroundWindowHeightFitScale = targetSize.height / getContentSize( ).height;

        setPosition( translate );
        setScale( backgroundWindowHeightFitScale, backgroundWindowHeightFitScale );

        auto listener = EventListenerTouchAllAtOnce::create( );
        listener->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        listener->onTouchesMoved = [ this, backgroundWindowHeightFitScale ] ( const std::vector<Touch*>& touches, Event* event )
        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );

            auto texS_2 = ( getContentSize( ) * backgroundWindowHeightFitScale ) / 2;
            auto winS_2 = visibleSize / 2;
            auto clearance = texS_2 - winS_2;

            for ( auto& obj : touches )
            {
                auto movedPos = getPosition( ) - translate + obj->getDelta( );
                if ( clearance.width * -1 <= clearance.width &&
                     clearance.height * -1 <= clearance.height )
                {
                    movedPos.clamp( clearance * -1, clearance );
                    setPosition( movedPos + translate );
                }
            }
        };
        listener->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( listener, this );

        return this;
    }

    LayerCity::LayerCity( std::string const& path )
        : path( path )
    {

    }
    LayerCity::~LayerCity( )
    {
    }
    bool LayerCity::init( )
    {
        if ( !Layer::init( ) ) return false;

        using namespace Lib;

        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        //{
        //    // オーディオ定義ファイルの読み込み  
        //    AudioManager::getInstance( )->readAudioListFile( "res/data/audio.json" );
        //    AudioManager::getInstance( )->playBgm( "city", 1.5f );
        //    AudioManager::getInstance( )->setBgmVolume( UserDefault::getInstance( )->getFloatForKey( u8"bgm" ) );
        //}

        jsonRead( );

        /**
         *  画面上部のメニュー
         */
        {
            auto board = Sprite::create( u8"res/texture/system/board.png" );
            auto boardPixel = board->getContentSize( ) / scale;
            auto boardScale = fitWidth( board, vs.width );
            board->setScale( boardScale, boardScale );
            board->setAnchorPoint( Vec2( 0, 1 ) );
            board->setPosition( Vec2( vo + Vec2( 0, vs.height ) ) );
            addChild( board );

            auto height = boardPixel.height - 10 * 2;
            if ( auto calendar = Calendar::create( )->make( ) )
            {
                board->addChild( calendar );
                calendar->setScale( fitHeight( calendar, height * scale ), fitHeight( calendar, height * scale ) );
                calendar->setPosition( Vec2( boardPixel ) * scale + Vec2( -10, -10 ) * scale );
            }

            if ( auto heart = HeartGauge::create( )->make( ) )
            {
                board->addChild( heart );
                heart->setScale( fitHeight( heart, height * scale ), fitHeight( heart, height * scale ) );
                heart->setPosition( Vec2( 0, boardPixel.height ) * scale + Vec2( 10, -10 ) * scale );
            }
        }

        /**
         *  画面下部のメニュー
         */
        {
            auto board = Sprite::create( u8"res/texture/system/board.png" );
            auto boardPixel = board->getContentSize( ) / scale;
            auto boardScale = fitWidth( board, vs.width );
            board->setScale( boardScale, boardScale );
            board->setAnchorPoint( Vec2( 0, 0 ) );
            board->setPosition( vo );
            addChild( board );

            auto height = boardPixel.height - 10 * 2;
            if ( auto button = createBackButton( ) )
            {
                board->addChild( button );
                button->setScale( fitHeight( button, height * scale ), fitHeight( button, height * scale ) );
                button->setPosition( Vec2( 10, 10 ) * scale );
            }

            if ( auto button = createOptionButton( ) )
            {
                board->addChild( button );
                button->setScale( fitHeight( button, height * scale ), fitHeight( button, height * scale ) );
                button->setPosition( Vec2( boardPixel.width - 10, 10 ) * scale );
            }
        }

        if ( auto sprite = Sprite::create( ) )
        {
            sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
            sprite->setAnchorPoint( Vec2( 0, 0 ) );
            sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
            sprite->setColor( Color3B( 0, 0, 0 ) );
            sprite->runAction( Sequence::create( FadeOut::create( 1.0F ), RemoveSelf::create( ), nullptr ) );
            addChild( sprite );
        }

        return true;
    }
    void LayerCity::setup( )
    {

    }
    void LayerCity::jsonRead( )
    {
        Json::Reader reader;
        if ( reader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( path, u8"res/data/" ) ), root ) )
        {
            auto map = root[u8"background"].asString( );
            auto background = CityMap::create( )->make( map );
            addChild( background );

            std::vector<ScenarioPointData> main;
            for ( auto& value : root[u8"point.main"] )
            {
                ScenarioPointData temp;
                temp.scenario = value[u8"scenario"].asString( );
                temp.visit = value[u8"visit"].asBool( );
                temp.position = Vec2( value[u8"position"][0].asInt( ),
                                      value[u8"position"][1].asInt( ) );
                main.emplace_back( temp );
            }
            std::vector<ScenarioPointData> sub;
            for ( auto& value : root[u8"point.sub"] )
            {
                ScenarioPointData temp;
                temp.scenario = value[u8"scenario"].asString( );
                temp.visit = value[u8"visit"].asBool( );
                temp.position = Vec2( value[u8"position"][0].asInt( ),
                                      value[u8"position"][1].asInt( ) );
                sub.emplace_back( temp );
            }

            int i = 0;
            for ( auto& obj : main )
            {
                auto mark = MainMark::create( );
                mark->pasteMap( background, obj );

                mark->setButtonEndCallBack( [ this, i ]
                {
                    root[u8"point.main"][i][u8"visit"] = true;
                    Json::StyledWriter writer;
                    writeUserLocal( writer.write( root ), u8"island.json" );

                    if ( auto sprite = Sprite::create( ) )
                    {
                        sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                        sprite->setAnchorPoint( Vec2( 0, 0 ) );
                        sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                        sprite->setOpacity( 0 );
                        sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ i, this ] { SceneManager::createNovel( root[u8"point.main"][i][u8"scenario"].asString( ) ); } ), RemoveSelf::create( ), nullptr ) );
                        addChild( sprite );
                    }
                } );
                ++i;
            }
            i = 0;
            for ( auto& obj : sub )
            {
                auto mark = SubMark::create( );
                mark->pasteMap( background, obj );

                mark->setButtonEndCallBack( [ this, i ]
                {
                    root[u8"point.sub"][i][u8"visit"] = true;
                    Json::StyledWriter writer;
                    writeUserLocal( writer.write( root ), u8"island.json" );

                    if ( auto sprite = Sprite::create( ) )
                    {
                        sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                        sprite->setAnchorPoint( Vec2( 0, 0 ) );
                        sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                        sprite->setOpacity( 0 );
                        sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ i, this ] { SceneManager::createNovel( root[u8"point.sub"][i][u8"scenario"].asString( ) ); } ), RemoveSelf::create( ), nullptr ) );
                        addChild( sprite );
                    }
                } );
                ++i;
            }
        }
    }
    cocos2d::ui::Button * LayerCity::createBackButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 0, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                SceneManager::createBreeding( );
            }
        } );
        return button;
    }
    cocos2d::ui::Button * LayerCity::createOptionButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/button.option.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 1, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                auto scene = Director::getInstance( )->getRunningScene( );
                auto layer = LayerOption::create( );
                layer->setup( );
                scene->addChild( layer );
            }
        } );
        return button;
    }
}
