#include "LayerCity.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include <vector>
#include <functional>

#include "../Novel/ScriptHeart.h"

#include "../../Lib/Utilitys.h"

#include "../../Lib/json.h"

#include "../System/DataSettings.h"

#include "LayerOption.h"

#include "../../Lib/AudioManager.h"

#include "LayerNovelView.h"

#include "../IslandMap/LayerIsland.h"

USING_NS_CC;

namespace User
{
    void LayerCityMark::setButtonEndCallBack( std::function<void( )>const& callback )
    {
        buttonEnd = callback;
    }
    void LayerCityMark::pasteMap( cocos2d::Sprite * map, ScenarioPointData const & data )
    {
        initScenarioPointData( data );

        auto pixel = map->getTexture( )->getContentSizeInPixels( );

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

        map->addChild( this );

        setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
        setScale( Lib::fitWidth( this, 128 * scale ), Lib::fitWidth( this, 128 * scale ) );
        if ( data.visit ) setEnabled( false );

        addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( buttonEnd )buttonEnd( );
            }
        } );
    }

    void MainMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.main.png" );
        loadTexturePressed( dir + "scenario.main.select.png" );

        LayerCityMark::pasteMap( map, data );
    }

    void SubMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.sub.png" );
        loadTexturePressed( dir + "scenario.sub.select.png" );

        LayerCityMark::pasteMap( map, data );

        setScale( getScale( ) * 0.5 );
    }


    bool Calendar::init( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        setPosition( vo + vs );

        const std::string dir = u8"res/texture/days/";

        day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );

        std::string path = dir + u8"calendar(" + StringUtils::toString( day ) + u8").png";
        if ( auto calendar = Sprite::create( path ) )
        {
            addChild( calendar );
            setContentSize( calendar->getContentSize( ) );
            calendar->setAnchorPoint( Vec2( 0, 0 ) );
            setAnchorPoint( Vec2( 1, 1 ) );
        }
        return true;
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
            removeChildByName( u8"ok.button" );
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

    LayerCity::LayerCity( std::string const& island_name )
        : island_name( island_name )
    {

    }
    LayerCity::~LayerCity( )
    {
        AudioManager::getInstance( )->stopBgm( 1.5F );
    }
    bool LayerCity::init( )
    {
        if ( !Layer::init( ) ) return false;

        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        AudioManager::getInstance( )->playBgm( "city", 1.5f );

        jsonRead( );

        /**
         *  画面上部のメニュー
         */
        {
            auto board = Sprite::create( u8"res/texture/system/board.png" );
            auto boardPixel = board->getContentSize( ) / scale;
            auto boardScale = Lib::fitWidth( board, vs.width );
            board->setScale( boardScale, boardScale );
            board->setAnchorPoint( Vec2( 0, 1 ) );
            board->setPosition( Vec2( vo + Vec2( 0, vs.height ) ) );
            addChild( board );

            auto width = boardPixel.width - 10 * 2;
            auto height = boardPixel.height - 10 * 2;
            auto calendar = Calendar::create( );
            if ( calendar )
            {
                board->addChild( calendar );
                calendar->setScale( Lib::fitHeight( calendar, height * scale ) );
                calendar->setPosition( Vec2( boardPixel ) * scale + Vec2( -10, -10 ) * scale );
            }

            std::string time_path = u8"res/texture/system/time." + StringUtils::toString( UserDefault::getInstance( )->getIntegerForKey( u8"時刻" ) ) + u8".png";
            auto time = Sprite::create( time_path );
            if ( time )
            {
                board->addChild( time );
                time->setAnchorPoint( Vec2( 1, 1 ) );
                time->setScale( Lib::fitHeight( calendar, height * scale ) );
                time->setPosition( Vec2( boardPixel ) * scale + Vec2( -10, -10 ) * scale + Vec2( -calendar->getContentSize( ).width * calendar->getScale( ), 0 ) );
            }

            auto heart = HeartGauge::create( )->make( );
            if ( heart )
            {
                heart->setAnchorPoint( Vec2( 0, 0.5 ) );
                heart->setScale( Lib::fitWidth( heart, ( board->getContentSize( ).width -
                                                         calendar->getContentSize( ).width * calendar->getScale( ) - 20/*下のずらしている分の10と、間に10pixel開けるためです。*/ * scale -
                                                         time->getContentSize( ).width * time->getScale( ) - 20 * scale ) ) );
                heart->setPosition( Vec2( 0, boardPixel.height * 0.5 ) * scale + Vec2( 10, 0 ) * scale );
                board->addChild( heart );
            }
        }

        /**
         *  画面下部のメニュー
         */
        {
            auto board = Sprite::create( u8"res/texture/system/board.png" );
            auto boardPixel = board->getContentSize( ) / scale;
            auto boardScale = Lib::fitWidth( board, vs.width );
            board->setScale( boardScale, boardScale );
            board->setAnchorPoint( Vec2( 0, 0 ) );
            board->setPosition( vo );
            addChild( board );

            auto height = boardPixel.height - 10 * 2;
            if ( auto button = createBackButton( ) )
            {
                board->addChild( button );
                button->setScale( Lib::fitHeight( button, height * scale ) );
                button->setPosition( Vec2( 10, 10 ) * scale );
            }

            if ( auto button = createTimeNextButton( ) )
            {
                addChild( button );
                button->setPosition( Vec2( board->getContentSize( ).width * board->getScale( ), board->getContentSize( ).height * board->getScale( ) ) );
            }

            if ( auto label = createLabel( island_name ) )
            {
                addChild( label );
                label->setPosition( Vec2( 0, board->getContentSize( ).height * board->getScale( ) ) );
            }
        }

        return true;
    }
    void LayerCity::setup( )
    {
        // フェードイン
        if ( auto sprite = Sprite::create( ) )
        {
            sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
            sprite->setAnchorPoint( Vec2( 0, 0 ) );
            sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
            sprite->setColor( Color3B( 0, 0, 0 ) );
            sprite->runAction( Sequence::create( FadeOut::create( 1.0F ), RemoveSelf::create( ), nullptr ) );
            addChild( sprite );
        }
    }
    void LayerCity::jsonRead( )
    {
        save_name = u8"autosave.json";

        removeChildByName( u8"background" );

        int now_day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        int now_time = UserDefault::getInstance( )->getIntegerForKey( u8"時刻" );

        Json::Reader reader;
        if ( reader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( save_name, u8"res/data/" ) ), root ) )
        {
            /**
            * 貼り付けるための背景を作成します。
            */
            auto map = root[island_name][u8"background"].asString( );
            auto background = CityMap::create( )->make( map );
            background->setName( u8"background" );
            addChild( background );

            /**
             * 強制イベントを読み込みます。
             */
            for ( auto& value : root[island_name][u8"point.force"] )
            {
                auto visit = value[u8"visit"].asBool( );
                /**
                 * 強制イベントの中で、未読のものがあったら次のフレームで、強制的にノベルのシーンに飛ばします。
                 */
                if ( !visit )
                {
                    ScenarioPointData data;
                    data.event = ScenarioPointData::Event::force;
                    data.initScenarioPointData( value );

                    if ( data.day_begin <= now_day &&
                         now_day <= data.day_end )
                        ;
                    else continue;

                    if ( data.time_begin <= now_time &&
                         now_time <= data.time_end )
                        ;
                    else continue;

                    auto mark = MainMark::create( );
                    mark->pasteMap( background, data );

                    scheduleOnce( [ this, &value, data ] ( float delay )
                    {
                        value[u8"visit"] = true;
                        Json::StyledWriter writer;
                        auto saveString = writer.write( root );
                        auto savePath = save_name;
                        Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( data, [ this, saveString, savePath ]
                        {
                            writeUserLocal( saveString, savePath );
                        } ) );
                    }, 0.0F, u8"force_event" );
                }
            }

            /**
             * メインシナリオを読み込んで貼り付けていきます。
             */
            for ( auto& value : root[island_name][u8"point.main"] )
            {
                ScenarioPointData data;
                data.event = ScenarioPointData::Event::main;
                data.initScenarioPointData( value );

                if ( data.day_begin <= now_day &&
                     now_day <= data.day_end )
                    ;
                else continue;

                if ( data.time_begin <= now_time &&
                     now_time <= data.time_end )
                    ;
                else continue;

                auto mark = MainMark::create( );
                mark->pasteMap( background, data );
                mark->setButtonEndCallBack( [ this, &value, data ]
                {
                    value[u8"visit"] = true;
                    Json::StyledWriter writer;
                    auto saveString = writer.write( root );
                    auto savePath = save_name;
                    Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( data, [ this, saveString, savePath ]
                    {
                        writeUserLocal( saveString, savePath );
                    } ) );
                } );
            }

            /**
             * サブシナリオを読み込んで貼り付けていきます。
             */
            for ( auto& value : root[island_name][u8"point.sub"] )
            {
                ScenarioPointData data;
                data.event = ScenarioPointData::Event::sub;
                data.initScenarioPointData( value );

                if ( data.day_begin <= now_day &&
                     now_day <= data.day_end )
                    ;
                else continue;

                if ( data.time_begin <= now_time &&
                     now_time <= data.time_end )
                    ;
                else continue;

                auto mark = SubMark::create( );
                mark->pasteMap( background, data );
                mark->setButtonEndCallBack( [ this, &value, data ]
                {
                    value[u8"visit"] = true;
                    Json::StyledWriter writer;
                    auto saveString = writer.write( root );
                    auto savePath = save_name;
                    Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( data, [ this, saveString, savePath ]
                    {
                        writeUserLocal( saveString, savePath );
                    } ) );
                } );
            }
        }
    }
    void LayerCity::time_next( )
    {
        using Islands = LayerIsland::Islands;

        Islands staying_island = (Islands)UserDefault::getInstance( )->getIntegerForKey( u8"滞在中の島" );

        std::vector<int> days =
        {
            0, 8, 4, 1
        };
        std::vector<std::string> point =
        {
            u8"無名の島",
            u8"ラシャス島",
            u8"ヒャルキシ島",
            u8"アイクラ島",
        };

        int sum = 0;
        for ( int i = Islands::none; i <= staying_island; ++i ) sum += days[i];
        auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        if ( day <= sum )
        {
            /* nothing */
        }
        else if ( staying_island < Islands::aikura )
        {
            staying_island = Islands( staying_island + 1 );
            UserDefault::getInstance( )->setIntegerForKey( u8"滞在中の島", staying_island );
        }

        island_name = point[staying_island];
        init( );
    }
    cocos2d::Label * LayerCity::createLabel( std::string const& title )
    {
        auto font = Label::createWithTTF( title,
                                          u8"res/fonts/HGRGE.TTC",
                                          64 * Director::getInstance( )->getContentScaleFactor( ) );
        font->setAnchorPoint( Vec2( 0.5F, 0 ) );
        font->setAnchorPoint( Vec2( 0, 0 ) );
        font->setTextColor( Color4B( 39, 39, 39, 255 ) );
        return font;
    }
    cocos2d::ui::Button * LayerCity::createBackButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png",
                                          u8"res/texture/system/backbutton.select.png" );

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
    cocos2d::ui::Button * LayerCity::createTimeNextButton( )
    {
        auto _scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/timer.png",
                                          u8"res/texture/system/timer.select.png" );

        button->setAnchorPoint( Vec2( 1, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            // 次に、時間を一段階進めます。
            // 朝→夕→夜
            auto time = UserDefault::getInstance( )->getIntegerForKey( u8"時刻" );
            if ( 3 <= ( time + 1 ) ) // 繰り上がったら
            {
                auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
                UserDefault::getInstance( )->setIntegerForKey( u8"日", day + 1 );
            }
            time = ( time + 1 ) % 3;
            UserDefault::getInstance( )->setIntegerForKey( u8"時刻", time );

            time_next( );
        } );
        return button;
    }
}
