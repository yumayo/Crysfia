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

#include "LayerMessageBox.h"

#include "LayerTutorialBox.h"

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
    }


    bool Calendar::init( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        setPosition( vo + vs );

        const std::string dir = u8"res/texture/diary/";

        day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );

        std::string path = dir + u8"diary_" + StringUtils::toString( day ) + u8".png";
        if ( auto calendar = Sprite::create( path ) )
        {
            addChild( calendar );
            setContentSize( calendar->getContentSize( ) );
            calendar->setAnchorPoint( Vec2( 0, 0 ) );
            setAnchorPoint( Vec2( 1, 1 ) );
        }
        return true;
    }

    bool CityMap::init( )
    {
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;

        honeycomb_size = Size( 95, 80.5 );
        map_size = Size( 19, 20 );
        start_position = Vec2( 168, 2048 - 220 );

        map = Sprite::create( u8"res/texture/system/map.select.png" );
        map->setScale( scale );
        setContentSize( map->getContentSize( ) * map->getScale( ) );
        addChild( map );

        translate = vo + vs * 0.5;

        setPosition( UserDefault::getInstance( )->getFloatForKey( u8"マップx" ),
                     UserDefault::getInstance( )->getFloatForKey( u8"マップy" ) );

        move_layer = Layer::create( );
        addChild( move_layer );
        event = EventListenerTouchOneByOne::create( );
        event->onTouchBegan = [ this ] ( Touch* touch, Event* e )
        {
            return true;
        };
        event->onTouchMoved = [ this ] ( Touch* touch, Event* e )
        {
            if ( touch->getStartLocation( ).distance( touch->getLocation( ) ) < 10 )
            {
            }
            else
            {
                if ( !is_move )
                {
                    // ゴミコード
                    // 一部のイベントだけをキャンセルできないかなー。
                    // http://qiita.com/Riyaaaa_a/items/15b1661e96653d17b4e1
                    // イベント中断参考になりました。
                    {
                        EventTouch event_touch;
                        event_touch.setEventCode( EventTouch::EventCode::CANCELLED );
                        event_touch.setTouches( std::vector<Touch*>{touch} );
                        Director::getInstance( )->getEventDispatcher( )->dispatchEvent( &event_touch );
                    }
                    // 中断した後に、通り抜け出来ないレイヤーとして認識させる。
                    event->setSwallowTouches( true );
                    // その後で、再び、マップを押したという命令を出せば、
                    // 後ろのボタンの方は無効になってくれる。
                    {
                        EventTouch event_touch;
                        event_touch.setEventCode( EventTouch::EventCode::BEGAN );
                        event_touch.setTouches( std::vector<Touch*>{touch} );
                        Director::getInstance( )->getEventDispatcher( )->dispatchEvent( &event_touch );
                    }
                    is_move = true;
                }

                auto visibleSize = Director::getInstance( )->getVisibleSize( );

                auto texS_2 = ( getContentSize( ) ) / 2;
                auto winS_2 = visibleSize / 2;
                auto clearance = texS_2 - winS_2;

                auto movedPos = getPosition( ) - translate + touch->getDelta( );
                if ( clearance.width * -1 <= clearance.width &&
                     clearance.height * -1 <= clearance.height )
                {
                    movedPos.clamp( clearance * -1, clearance );
                    setPosition( movedPos + translate );
                }
            }
        };
        event->onTouchEnded = [ this ] ( Touch* touch, Event* e )
        {
            event->setSwallowTouches( false );
            is_move = false;

            UserDefault::getInstance( )->setFloatForKey( u8"マップx", getPosition( ).x );
            UserDefault::getInstance( )->setFloatForKey( u8"マップy", getPosition( ).y );
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( event, move_layer );

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

        map->addChild( icon );
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
            Vec2( -move.x, move.y );
        return  MoveTo::create( 0.3F, pos );
    }

    void CityMap::set_position( int const x, int const y )
    {
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;
        Vec2 const slide = ( y & 1 ) == 0 ? Vec2( ) : Vec2( honeycomb_size.width * 0.5F, 0 );

        Vec2 move = Vec2( start_position.x, 2048 - start_position.y ) + Vec2( x * honeycomb_size.width, y * honeycomb_size.height ) + slide;
        Vec2 pos = Vec2( vs ) * 0.5 + Vec2( getContentSize( ).width * 0.5, -getContentSize( ).height * 0.5 ) +
            Vec2( -move.x, move.y );
        setPosition( pos );
    }

    void CityMap::set_disable( )
    {
        this->getEventDispatcher( )->pauseEventListenersForTarget( move_layer );
    }

    void CityMap::set_enable( )
    {
        this->getEventDispatcher( )->resumeEventListenersForTarget( move_layer );
        UserDefault::getInstance( )->setFloatForKey( u8"マップx", getPosition( ).x );
        UserDefault::getInstance( )->setFloatForKey( u8"マップy", getPosition( ).y );
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

        if ( !UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) )
        {
            jsonRead( );
        }
        else
        {
            json_read_game_clear( );
        }

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
            board->setName( u8"under_board" );
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

            Action( );

            if ( !UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) )
            {
                if ( auto button = createTimeNextButton( ) )
                {
                    button->setName( u8"time_button" );
                    button->setScale( scale );
                    //button->setOpacity( 0 );
                    //button->runAction( FadeIn::create( 0.3F ) );
                    button->setPosition( Vec2( board->getContentSize( ).width * board->getScale( ), board->getContentSize( ).height * board->getScale( ) ) );
                    addChild( button );
                }

                //if ( auto label = createLabel( UserDefault::getInstance( )->getStringForKey( u8"滞在中の島" ) ) )
                //{
                //    //label->setOpacity( 0 );
                //    //label->runAction( FadeIn::create( 0.3F ) );
                //    label->setScale( scale );
                //    label->setPosition( Vec2( 0, board->getContentSize( ).height * board->getScale( ) ) );
                //    addChild( label );
                //}
            }
        }

        if ( !mark_ptr_stack.empty( ) )
        {
            animation_start( );
            addChild( LayerMessageBox::create( u8"期限を過ぎたシナリオがあります。", [ this ] { read_check( ); } ) );
        }
        else if ( !mark_stack.empty( ) )
        {
            animation_start( );
            addChild( LayerMessageBox::create( u8"新しくシナリオが読めます！", [ this ] { event_recovery( ); } ) );
        }
        else
        {
            animation_end( );
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
            map = CityMap::create( );
            map->setName( u8"CityMap" );
            addChild( map );
            for ( auto& island : root )
            {
                // 強制イベントを読み込みます。
                for ( auto& value : island[u8"point.force"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );

                    // スポーンしたことのないものの中で、
                    // 滞在期間中のもの。
                    // 要するに新規に読めるシナリオ。
                    // それらは、アニメーションさせて登場させます。
                    if ( !temp.visit && !temp.spawn && temp.is_stay( ) )
                    {
                        mark_stack.push( [ this, &value ] ( ) {
                            value[u8"spawn"] = true; set_force_mark( value ); } );
                        stack_mark_pos( value );
                        continue;
                    }
                    // スポーンしていたのに、訪れることの出来なかったらシナリオにはバツマークを付けます。
                    if ( !temp.visit && temp.spawn && !temp.is_stay( ) && !temp.read_not )
                    {
                        auto mark = set_force_mark( value );
                        mark->setEnabled( true );
                        mark_ptr_stack.push( [ this, &value, mark ] ( )
                        {
                            value[u8"read_not"] = true;
                            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
                            p->setAnchorPoint( Vec2( 0, 0 ) );
                            mark->addChild( p );
                            mark->setEnabled( false );
                        } );
                        stack_mark_ptr_pos( value );
                        continue;
                    }
                    // スポーンしていたら、
                    if ( temp.spawn )
                    {
                        set_force_mark( value );
                    }
                }
                // メインシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.main"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );

                    // スポーンしたことのないものの中で、
                    // 滞在期間中のもの。
                    // 要するに新規に読めるシナリオ。
                    // それらは、アニメーションさせて登場させます。
                    if ( !temp.visit && !temp.spawn && temp.is_stay( ) )
                    {
                        mark_stack.push( [ this, &value ] ( ) {
                            value[u8"spawn"] = true; set_main_mark( value ); } );
                        stack_mark_pos( value );
                        continue;
                    }
                    // スポーンしていたのに、訪れることの出来なかったらシナリオにはバツマークを付けます。
                    if ( !temp.visit && temp.spawn && !temp.is_stay( ) && !temp.read_not )
                    {
                        auto mark = set_main_mark( value );
                        mark->setEnabled( true );
                        mark_ptr_stack.push( [ this, &value, mark ] ( )
                        {
                            value[u8"read_not"] = true;
                            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
                            p->setAnchorPoint( Vec2( 0, 0 ) );
                            mark->addChild( p );
                            mark->setEnabled( false );
                        } );
                        stack_mark_ptr_pos( value );
                        continue;
                    }
                    // スポーンしていたら、
                    if ( temp.spawn )
                    {
                        set_main_mark( value );
                    }
                }
                // サブシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.sub"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );

                    // スポーンしたことのないものの中で、
                    // 滞在期間中のもの。
                    // 要するに新規に読めるシナリオ。
                    // それらは、アニメーションさせて登場させます。
                    if ( !temp.visit && !temp.spawn && temp.is_stay( ) )
                    {
                        mark_stack.push( [ this, &value ] ( ) {
                            value[u8"spawn"] = true; set_sub_mark( value ); } );
                        stack_mark_pos( value );
                        continue;
                    }
                    // スポーンしていたのに、訪れることの出来なかったらシナリオにはバツマークを付けます。
                    if ( !temp.visit && temp.spawn && !temp.is_stay( ) && !temp.read_not )
                    {
                        auto mark = set_sub_mark( value );
                        mark->setEnabled( true );
                        mark_ptr_stack.push( [ this, &value, mark ] ( )
                        {
                            value[u8"read_not"] = true;
                            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
                            p->setAnchorPoint( Vec2( 0, 0 ) );
                            mark->addChild( p );
                            mark->setEnabled( false );
                        } );
                        stack_mark_ptr_pos( value );
                        continue;
                    }
                    // スポーンしていたら、
                    if ( temp.spawn )
                    {
                        set_sub_mark( value );
                    }
                }
            }
        }
    }
    void User::LayerCity::json_read_game_clear( )
    {
        save_name = u8"autosave.json";
        Json::Reader reader;
        if ( reader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( save_name, u8"res/data/" ) ), root ) )
        {
            map = CityMap::create( );
            map->setName( u8"CityMap" );
            addChild( map );
            for ( auto& island : root )
            {
                // 強制イベントを読み込みます。
                for ( auto& value : island[u8"point.force"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );
                    temp.event = ScenarioPointData::Event::force;
                    bool temp_visit = temp.visit;
                    temp.visit = false;
                    auto mark = MainMark::create( );
                    mark->pasteMap( map, temp );
                    temp.visit = temp_visit;
                    mark->setButtonEndCallBack( [ temp ]
                    {
                        Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( temp, [ ] { } ) );
                    } );
                }
                // メインシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.main"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );
                    temp.event = ScenarioPointData::Event::main;
                    bool temp_visit = temp.visit;
                    temp.visit = false;
                    auto mark = MainMark::create( );
                    mark->pasteMap( map, temp );
                    temp.visit = temp_visit;
                    mark->setButtonEndCallBack( [ temp ]
                    {
                        Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( temp, [ ] { } ) );
                    } );
                }
                // サブシナリオを読み込んで貼り付けていきます。
                for ( auto& value : island[u8"point.sub"] )
                {
                    ScenarioPointData temp;
                    temp.initScenarioPointData( value );
                    temp.event = ScenarioPointData::Event::sub;
                    bool temp_visit = temp.visit;
                    temp.visit = false;
                    auto mark = SubMark::create( );
                    mark->pasteMap( map, temp );
                    temp.visit = temp_visit;
                    mark->setButtonEndCallBack( [ temp ]
                    {
                        Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( temp, [ ] { } ) );
                    } );
                }
            }
        }

        if ( UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリア" ) &&
             !UserDefault::getInstance( )->getBoolForKey( u8"ゲームクリアダイアログ" ) )
        {
            addChild( LayerMessageBox::create( u8"ゲームクリアおめでとうございます！", [ this ] {
                addChild( LayerMessageBox::create( u8"全てのシナリオが開放されました。", [ ] {
                    UserDefault::getInstance( )->setBoolForKey( u8"ゲームクリアダイアログ", true ); } ) ); } ) );
        }
    }
    void LayerCity::time_next( )
    {
        Lib::next_day( );

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

    void User::ScenarioPointData::initScenarioPointData( Json::Value const & root )
    {
        scenario = root[u8"scenario"].asString( );
        visit = root[u8"visit"].asBool( );
        spawn = root[u8"spawn"].asBool( );
        read_not = root[u8"read_not"].asBool( );
        position = cocos2d::Vec2( root[u8"position"][0].asInt( ),
                                  root[u8"position"][1].asInt( ) );
        title = root[u8"title"].asString( );

        auto& day = root[u8"day"];
        switch ( day.size( ) )
        {
        case 1:
            day_begin = day[0].asInt( );
            day_end = day[0].asInt( );
            break;
        case 2:
            day_begin = day[0].asInt( );
            day_end = day[1].asInt( );
            break;
        default:
            break;
        }

        // サブ記入変数
        // もしかしたらない可能性もあるので。
        morning = root[u8"morning"].isNull( ) ? morning : root[u8"morning"].asBool( );
        daytime = root[u8"daytime"].isNull( ) ? daytime : root[u8"daytime"].asBool( );
        night = root[u8"night"].isNull( ) ? night : root[u8"night"].asBool( );
    }

    bool ScenarioPointData::is_stay( ) const
    {
        auto now_day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        auto now_time = static_cast<Times>( UserDefault::getInstance( )->getIntegerForKey( u8"時刻" ) );

        if ( day_begin <= now_day &&
             now_day <= day_end )
            ;
        else return false;

        switch ( now_time )
        {
        case User::ScenarioPointData::Times::morning:
            return morning;
            break;
        case User::ScenarioPointData::Times::daytime:
            return daytime;
            break;
        case User::ScenarioPointData::Times::night:
            return night;
            break;
        default:
            return false;
            break;
        }

        return true;
    }
    int User::ScenarioPointData::get_dead_line( ) const
    {
        int now_day = UserDefault::getInstance( )->getIntegerForKey( u8"日" );
        int dead_line = day_end - now_day; // 12 - 10 -> 2, 9 - 10 -> -1
        if ( dead_line < 0 ) dead_line = 0;
        return dead_line;
    }
    LayerCityMark* LayerCity::set_force_mark( Json::Value& value )
    {
        ScenarioPointData data;
        data.initScenarioPointData( value );
        bool stay = data.is_stay( );
        data.event = ScenarioPointData::Event::force;

        auto mark = MainMark::create( );
        mark->pasteMap( map, data );
        if ( !stay )mark->setEnabled( false );
        if ( data.read_not )
        {
            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
            p->setAnchorPoint( Vec2( 0, 0 ) );
            mark->addChild( p );
        }
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
                    value[u8"visit"] = false;
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
    LayerCityMark* LayerCity::set_main_mark( Json::Value& value )
    {
        ScenarioPointData data;
        data.initScenarioPointData( value );
        bool stay = data.is_stay( );
        data.event = ScenarioPointData::Event::main;

        auto mark = MainMark::create( );
        mark->pasteMap( map, data );
        if ( !stay ) mark->setEnabled( false );
        if ( data.read_not )
        {
            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
            p->setAnchorPoint( Vec2( 0, 0 ) );
            mark->addChild( p );
        }
        mark->setButtonEndCallBack( [ this, &value, data ]
        {
            value[u8"visit"] = true;
            Json::StyledWriter writer;
            auto saveString = writer.write( root );
            value[u8"visit"] = false;
            auto savePath = save_name;
            Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( data, [ this, saveString, savePath ]
            {
                writeUserLocal( saveString, savePath );
            } ) );
        } );

        return mark;
    }
    LayerCityMark* LayerCity::set_sub_mark( Json::Value& value )
    {
        ScenarioPointData data;
        data.initScenarioPointData( value );
        bool stay = data.is_stay( );
        data.event = ScenarioPointData::Event::sub;

        auto mark = SubMark::create( );
        mark->pasteMap( map, data );
        if ( !stay ) mark->setEnabled( false );
        if ( data.read_not )
        {
            auto p = Sprite::create( u8"res/texture/system/read_out.png" );
            p->setAnchorPoint( Vec2( 0, 0 ) );
            mark->addChild( p );
        }
        mark->setButtonEndCallBack( [ this, &value, data ]
        {
            value[u8"visit"] = true;
            Json::StyledWriter writer;
            auto saveString = writer.write( root );
            value[u8"visit"] = false;
            auto savePath = save_name;
            Director::getInstance( )->getRunningScene( )->addChild( LayerNovelView::create( data, [ this, saveString, savePath ]
            {
                writeUserLocal( saveString, savePath );
            } ) );
        } );

        return mark;
    }
    void User::LayerCity::animation_start( )
    {
        is_animation = true;
        if ( auto p = dynamic_cast<CityMap*>( getChildByName( u8"CityMap" ) ) )
        {
            p->set_disable( );
        }
        if ( auto p = dynamic_cast<ui::Button*>( getChildByName( u8"time_button" ) ) )
        {
            p->setEnabled( false );
        }
    }
    void User::LayerCity::animation_end( )
    {
        is_animation = false;
        Json::StyledWriter writer;
        writeUserLocal( writer.write( root ), save_name );
        if ( auto p = dynamic_cast<CityMap*>( getChildByName( u8"CityMap" ) ) )
        {
            p->set_enable( );
        }
        if ( auto p = dynamic_cast<ui::Button*>( getChildByName( u8"time_button" ) ) )
        {
            p->setEnabled( true );
        }
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
    void LayerCity::event_recovery( )
    {
        if ( mark_stack.empty( ) || force_event )
        {
            animation_end( );
        }
        else
        {
            auto delay = DelayTime::create( 0.1F );
            auto spawn = CallFunc::create( [ this ]
            {
                AudioManager::getInstance( )->playSe( u8"res/sound/button_spawn.mp3" );

                if ( mark_stack.top( ) ) mark_stack.top( )( );
            } );
            int x = mark_pos_stack.top( ).x;
            int y = mark_pos_stack.top( ).y;
            auto move = map->move_action( x, y );
            auto pop = CallFunc::create( [ this ]
            {
                mark_stack.pop( );
                mark_pos_stack.pop( );
            } );

            auto seq = Sequence::create( delay, move, spawn, pop, nullptr );

            map->runAction( Sequence::create( seq, CallFunc::create( [ this ] { event_recovery( ); } ), nullptr ) );
        }
    }
    void User::LayerCity::event_recovery_skip( )
    {
        while ( !( mark_stack.empty( ) || force_event ) )
        {
            // delay
            // move
            int x = mark_pos_stack.top( ).x;
            int y = mark_pos_stack.top( ).y;
            map->set_position( x, y );
            // spawn
            if ( mark_stack.top( ) ) mark_stack.top( )( );
            // pop
            mark_stack.pop( );
            mark_pos_stack.pop( );
        }
        animation_end( );
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
    void LayerCity::read_check( )
    {
        if ( mark_ptr_stack.empty( ) )
        {
            addChild( LayerMessageBox::create( u8"新しくシナリオが読めます！", [ this ] { event_recovery( ); } ) );
        }
        else
        {
            auto delay = DelayTime::create( 0.1F );
            auto check = CallFunc::create( [ this ] 
            {
                AudioManager::getInstance( )->playSe( u8"res/sound/button_read_not.mp3" );

                if ( mark_ptr_stack.top( ) ) mark_ptr_stack.top( )( );
            } );
            int x = mark_ptr_pos_stack.top( ).x;
            int y = mark_ptr_pos_stack.top( ).y;
            auto move = map->move_action( x, y );
            auto pop = CallFunc::create( [ this ]
            {
                mark_ptr_stack.pop( );
                mark_ptr_pos_stack.pop( );
            } );

            auto seq = Sequence::create( delay, move, check, pop, nullptr );

            map->runAction( Sequence::create( seq, CallFunc::create( [ this ] { read_check( ); } ), nullptr ) );
        }
    }

    void User::LayerCity::read_check_skip( )
    {
        while ( !( mark_ptr_stack.empty( ) ) )
        {
            // delay
            // move
            int x = mark_ptr_pos_stack.top( ).x;
            int y = mark_ptr_pos_stack.top( ).y;
            map->set_position( x, y );
            // check
            if ( mark_ptr_stack.top( ) ) mark_ptr_stack.top( )( );
            // pop
            mark_ptr_stack.pop( );
            mark_ptr_pos_stack.pop( );
        }
        addChild( LayerMessageBox::create( u8"新しくシナリオが読めます！", [ this ] { event_recovery( ); } ) );
    }
}
