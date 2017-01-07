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

USING_NS_CC;

namespace User
{
    void LayerCityMark::setButtonEndCallBack( std::function<void( )>const& callback )
    {
        buttonEnd = callback;
    }
    void LayerCityMark::pasteMap( CityMap* map, ScenarioPointData const & data )
    {
        initScenarioPointData( data );

        auto pixel = map->getTexture( )->getContentSizeInPixels( );

        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        // マップの方で、ポジションを指定するので用済みになりました。
        // setPosition( Vec2( position.x, pixel.height - position.y ) * _scale );

        if ( data.visit ) setEnabled( false );

        addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( buttonEnd )buttonEnd( );
            }
        } );
    }

    void MainMark::pasteMap( CityMap* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.main.png" );
        loadTexturePressed( dir + "scenario.main.select.png" );

        LayerCityMark::pasteMap( map, data );

        map->paste( this, position.x, position.y );
    }

    void SubMark::pasteMap( CityMap* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.sub.png" );
        loadTexturePressed( dir + "scenario.sub.select.png" );

        LayerCityMark::pasteMap( map, data );

        map->paste( this, position.x, position.y );

        // これもマップの方で設定するので用済みです。
        //setScale( getScale( ) * 0.5F );
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

    bool CityMap::init( int const x, int const y )
    {
        honeycomb_size = Size( 95, 80.5 );
        map_size = Size( 19, 20 );
        start_position = Vec2( 168, 2048 - 220 );

        initWithFile( u8"res/texture/system/map.select.png" );

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        translate = vo + vs * 0.5;

        Vec2 const slide = ( y & 1 ) == 0 ? Vec2( ) : Vec2( honeycomb_size.width * 0.5F, 0 );

        Vec2 move = Vec2( start_position.x, 2048 - start_position.y ) + Vec2( x * honeycomb_size.width, y * honeycomb_size.height ) + slide;
        setPosition( Vec2( vs ) * 0.5 + Vec2( getContentSize( ).width * 0.5, -getContentSize( ).height * 0.5 ) +
                     Vec2( -move.x, move.y ) * _scale );

        auto listener = EventListenerTouchAllAtOnce::create( );
        listener->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            removeChildByName( u8"ok.button" );
        };
        listener->onTouchesMoved = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );

            auto texS_2 = ( getContentSize( ) ) / 2;
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

        // 実験的な配列のテスト。
        //for ( int y = 0; y < map_size.height; ++y )
        //{
        //    for ( int x = 0; x < map_size.width; ++x )
        //    {
        //        auto icon = ui::Button::create( u8"res/texture/system/scenario.sub.png",
        //                                        u8"res/texture/system/scenario.sub.select.png" );
        //        paste( icon, x, y );
        //    }
        //}

        return true;
    }

    void CityMap::paste( cocos2d::ui::Button * icon, int const x, int const y )
    {
        Vec2 const slide = ( y & 1 ) == 0 ? Vec2( ) : Vec2( honeycomb_size.width * 0.5F, 0 );
        auto const scale = Director::getInstance( )->getContentScaleFactor( );
        auto const _scale = 1.0F / scale;

        icon->setPosition( start_position * _scale + Vec2( x * honeycomb_size.width, -y * honeycomb_size.height ) * _scale + slide * _scale );
        icon->setScale( Lib::fitHeight( icon, 86 * _scale ) );

    #ifdef _DEBUG // アイコンの上に配列番号を描画します。
        icon->setTitleFontName( u8"res/fonts/HGRGE.TTC" );
        icon->setTitleFontSize( 35 * _scale );
        icon->setTitleText( StringUtils::format( u8"[%d, %d]", x, y ) );
    #endif

        addChild( icon );
    }

    void CityMap::paste( MainMark * icon, int const x, int const y )
    {
        paste( static_cast<cocos2d::ui::Button*>( icon ), x, y );
    }

    void CityMap::paste( SubMark * icon, int const x, int const y )
    {
        paste( static_cast<cocos2d::ui::Button*>( icon ), x, y );
        icon->setScale( icon->getScale( ) * 0.75 );
    }

    cocos2d::MoveTo * CityMap::move_action( int const x, int const y )
    {
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;
        Vec2 const slide = ( y & 1 ) == 0 ? Vec2( ) : Vec2( honeycomb_size.width * 0.5F, 0 );

        Vec2 move = Vec2( start_position.x, 2048 - start_position.y ) + Vec2( x * honeycomb_size.width, y * honeycomb_size.height ) + slide;
        Vec2 pos = Vec2( vs ) * 0.5 + Vec2( getContentSize( ).width * 0.5, -getContentSize( ).height * 0.5 ) +
            Vec2( -move.x, move.y ) * _scale;
        return  MoveTo::create( 0.3F, pos );
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

        scheduleOnce( [ this ] ( float delay )
        {
            AudioManager::getInstance( )->playBgm( "city", 1.5f );
        }, 0.0F, u8"bgm_delay" );

        setIslandName( );

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

            if ( auto label = createLabel( UserDefault::getInstance( )->getStringForKey( u8"滞在中の島" ) ) )
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
        Json::Reader reader;
        if ( reader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( save_name, u8"res/data/" ) ), root ) )
        {
            /**
             * 貼り付けるための背景を作成します。
             */
            auto& position = root[UserDefault::getInstance( )->getStringForKey( u8"滞在中の島" )][u8"position"];
            int x = 0, y = 0;
            switch ( position.size( ) )
            {
            case 2:
                x = position[0].asInt( );
                y = position[1].asInt( );
                break;
            default:
                break;
            }
            auto map = CityMap::create( x, y );
            addChild( map );
            for ( auto& island : root )
            {
                // 強制イベントを読み込みます。
                for ( auto& value : island[u8"point.force"] )
                {
                    if ( mark_spawned_check( value ) )
                    {
                        auto mark = set_force_mark( value, map );
                    }
                    // スポーンしたことのないものの中で、
                    // 滞在期間中のもの。
                    // 要するに新規に読めるシナリオ。
                    // それらは、アニメーションさせて登場させます。
                    else if ( mark_stay_check( value ) )
                    {
                        mark_stack.push( [ this, &value, map ] ( ) {
                            value[u8"spawn"] = true; set_force_mark( value, map ); } );
                        stack_mark_pos( value );
                    }
                }
                // メインシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.main"] )
                {
                    if ( mark_spawned_check( value ) )
                    {
                        auto mark = set_main_mark( value, map );
                    }
                    else if ( mark_stay_check( value ) )
                    {
                        mark_stack.push( [ this, &value, map ] ( ) {
                            value[u8"spawn"] = true; set_main_mark( value, map ); } );
                        stack_mark_pos( value );
                    }
                }
                // サブシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.sub"] )
                {
                    if ( mark_spawned_check( value ) )
                    {
                        auto mark = set_sub_mark( value, map );
                    }
                    else if ( mark_stay_check( value ) )
                    {
                        mark_stack.push( [ this, &value, map ] ( ) {
                            value[u8"spawn"] = true; set_sub_mark( value, map ); } );
                        stack_mark_pos( value );
                    }
                }
            }
            event_recovery( map );
        }
    }
    void LayerCity::time_next( )
    {
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

        Json::StyledWriter writer;
        writeUserLocal( writer.write( root ), save_name );

        removeAllChildrenWithCleanup( true );
        init( );
    }
    cocos2d::Label * LayerCity::createLabel( std::string const& title )
    {
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        auto font = Label::createWithTTF( title,
                                          u8"res/fonts/HGRGE.TTC",
                                          64 );

        font->setScale( Lib::fitHeight( font, 64 * scale ) );
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
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        auto button = ui::Button::create( u8"res/texture/system/timer.png",
                                          u8"res/texture/system/timer.select.png" );

        button->setScale( Lib::fitHeight( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 1, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;



            time_next( );
        } );
        return button;
    }
    void LayerCity::setIslandName( )
    {
        std::vector<int> days =
        {
            0, 0, 8, 4, 1
        };

        auto sum = [ & ] ( int end )
        {
            int a = 0;
            for ( int i = 0; i <= end; ++i )
            {
                a += days[i];
            }
            return a;
        };

        auto day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        if ( day <= sum( 0 ) )
        {
            UserDefault::getInstance( )->setStringForKey( u8"滞在中の島", u8"無名の島" );
        }
        else if ( day <= sum( 1 ) )
        {
            UserDefault::getInstance( )->setStringForKey( u8"滞在中の島", u8"旅立ちの島" );
        }
        else if ( day <= sum( 2 ) ) // 8 <= 8 true 9 <= 8 false
        {
            UserDefault::getInstance( )->setStringForKey( u8"滞在中の島", u8"ラシャス島" );
        }
        else if ( day <= sum( 3 ) )
        {
            UserDefault::getInstance( )->setStringForKey( u8"滞在中の島", u8"ヒャルキシ島" );
        }
        else if ( day <= sum( 4 ) )
        {
            UserDefault::getInstance( )->setStringForKey( u8"滞在中の島", u8"アイクラ島" );
        }
    }
    bool LayerCity::mark_spawned_check( Json::Value & value )
    {
        ScenarioPointData scenario;
        scenario.initScenarioPointData( value );
        if ( scenario.spawn ) return true;
        return false;
    }
    bool LayerCity::mark_spawned_not_read_check( Json::Value & value )
    {
        ScenarioPointData scenario;
        bool stay = mark_stay_check_with_make( value, scenario );

        // マップに配置されていて、まだ読んだことなくて、読める期間から過ぎてしまった場合。
        if ( scenario.spawn && !scenario.visit && !stay && !scenario.read_not ) return true;
        return false;
    }
    bool LayerCity::mark_stay_check( Json::Value & value )
    {
        int now_day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        int now_time = UserDefault::getInstance( )->getIntegerForKey( u8"時刻" );

        ScenarioPointData scenario;
        scenario.initScenarioPointData( value );

        if ( scenario.day_begin <= now_day &&
             now_day <= scenario.day_end )
            ;
        else return false;

        if ( scenario.time_begin <= now_time &&
             now_time <= scenario.time_end )
            ;
        else return false;

        return true;
    }
    bool LayerCity::mark_stay_check_with_make( Json::Value & value, ScenarioPointData& scenario )
    {
        int now_day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        int now_time = UserDefault::getInstance( )->getIntegerForKey( u8"時刻" );

        scenario.initScenarioPointData( value );

        if ( scenario.day_begin <= now_day &&
             now_day <= scenario.day_end )
            ;
        else return false;

        if ( scenario.time_begin <= now_time &&
             now_time <= scenario.time_end )
            ;
        else return false;

        return true;
    }
    LayerCityMark* LayerCity::set_force_mark( Json::Value& value, CityMap* map )
    {
        ScenarioPointData data;
        bool stay = mark_stay_check_with_make( value, data );
        data.event = ScenarioPointData::Event::force;

        auto mark = MainMark::create( );
        mark->pasteMap( map, data );
        if ( !stay )mark->setEnabled( false );

        // 強制イベントの中で、未読のものがあったら次のフレームで、強制的にノベルのシーンに飛ばします。
        if ( !value[u8"visit"].asBool( ) )
        {
            if ( stay )
            {
                force_event = true;
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

        return mark;
    }
    LayerCityMark* LayerCity::set_main_mark( Json::Value& value, CityMap* map )
    {
        ScenarioPointData data;
        bool stay = mark_stay_check_with_make( value, data );
        data.event = ScenarioPointData::Event::main;

        auto mark = MainMark::create( );
        mark->pasteMap( map, data );
        if ( !stay ) mark->setEnabled( false );

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

        return mark;
    }
    LayerCityMark* LayerCity::set_sub_mark( Json::Value& value, CityMap* map )
    {
        ScenarioPointData data;
        bool stay = mark_stay_check_with_make( value, data );
        data.event = ScenarioPointData::Event::sub;

        auto mark = SubMark::create( );
        mark->pasteMap( map, data );
        if ( !stay ) mark->setEnabled( false );

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

        return mark;
    }
    void LayerCity::stack_mark_pos( Json::Value & value )
    {
        auto& position = value[u8"position"];
        int x = 0, y = 0;
        switch ( position.size( ) )
        {
        case 2:
            x = position[0].asInt( );
            y = position[1].asInt( );
            break;
        default:
            break;
        }
        mark_pos_stack.push( Vec2( x, y ) );
    }
    void LayerCity::event_recovery( CityMap* map )
    {
        if ( mark_stack.empty( ) || force_event )
            ;
        else
        {
            auto delay = DelayTime::create( 0.1F );
            auto spawn = CallFunc::create( [ this ]
            {
                if ( mark_stack.top( ) ) mark_stack.top( )( );
            } );
            auto move = map->move_action( mark_pos_stack.top( ).x, mark_pos_stack.top( ).y );
            auto pop = CallFunc::create( [ this ]
            {
                mark_stack.pop( );
                mark_pos_stack.pop( );
            } );

            auto seq = Sequence::create( delay, move, spawn, pop, nullptr );

            map->runAction( Sequence::create( seq, CallFunc::create( [ this, map ] { event_recovery( map ); } ), nullptr ) );
        }
    }
    void LayerCity::stack_mark_ptr_pos( Json::Value & value )
    {
        auto& position = value[u8"position"];
        int x = 0, y = 0;
        switch ( position.size( ) )
        {
        case 2:
            x = position[0].asInt( );
            y = position[1].asInt( );
            break;
        default:
            break;
        }
        mark_ptr_pos_stack.push( Vec2( x, y ) );
    }
    void LayerCity::read_check( CityMap* map )
    {
        if ( mark_ptr_stack.empty( ) )
            ;
        else
        {
            auto delay = DelayTime::create( 0.1F );
            auto check = CallFunc::create( [ this ]
            {
                auto p = Sprite::create( u8"res/texture/system/read.png" );
                p->setAnchorPoint( Vec2( 0, 0 ) );
                if ( mark_ptr_stack.top( ) )
                {
                   auto mark = mark_ptr_stack.top( )( );
                   mark->addChild( p );
                }
            } );
            auto move = map->move_action( mark_ptr_pos_stack.top( ).x, mark_ptr_pos_stack.top( ).y );
            auto pop = CallFunc::create( [ this ]
            {
                mark_ptr_stack.pop( );
                mark_ptr_pos_stack.pop( );
            } );

            auto seq = Sequence::create( delay, move, check, pop, nullptr );

            map->runAction( Sequence::create( seq, CallFunc::create( [ this, map ] { read_check( map ); } ), nullptr ) );
        }
    }
}
