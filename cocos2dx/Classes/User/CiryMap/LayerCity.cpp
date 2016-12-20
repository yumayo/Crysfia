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
        setScale( Lib::fitWidth( this, 128 * scale ), Lib::fitWidth( this, 128 * scale ) );
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

                    auto fitButton = Lib::fitWidth( kuroe, 128 * scale );
                    node->setScale( fitButton );

                    auto ok = ui::Button::create( dir + u8"ok.png" );
                    auto okPixel = ok->getContentSize( ) / scale;
                    node->addChild( ok );
                    ok->setPosition( Vec2( 0, -kuroePixel.height / 2 - okPixel.height / 2 ) * scale );
                    ok->addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
                    {
                        if ( type == ui::Widget::TouchEventType::ENDED )
                        {
                            map->pause( );
                            if ( buttonEnd ) buttonEnd( );
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

    LayerCity::LayerCity( std::string const& island_name )
        : island_name( island_name )
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
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        AudioManager::getInstance( )->playBgm( "city", 1.5f );

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

            auto width = boardPixel.width - 10 * 2;
            auto height = boardPixel.height - 10 * 2;
            auto calendar = Calendar::create( )->make( );
            if ( calendar )
            {
                board->addChild( calendar );
                calendar->setScale( fitHeight( calendar, height * scale ), fitHeight( calendar, height * scale ) );
                calendar->setPosition( Vec2( boardPixel ) * scale + Vec2( -10, -10 ) * scale );
            }

            auto heart = HeartGauge::create( )->make( );
            if ( heart )
            {
                heart->setAnchorPoint( Vec2( 0, 0.5 ) );
                heart->setScale( fitWidth( heart, board->getContentSize( ).width - calendar->getContentSize( ).width ) );
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

            if ( auto label = createLabel( island_name ) )
            {
                board->addChild( label );
                label->setPosition( Vec2( 0, board->getContentSize( ).height ) );
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
        save_name = u8"island.json";

        removeChildByName( u8"background" );

        Json::Reader reader;
        if ( reader.parse( FileUtils::getInstance( )->getStringFromFile( getLocalReadPath( save_name, u8"res/data/" ) ), root ) )
        {
            /**
             * 強制イベントを読み込みます。
             */
            for ( auto& value : root[island_name][u8"point.force"] )
            {
                auto scenario = value[u8"scenario"].asString( );
                auto visit = value[u8"visit"].asBool( );

                /**
                 * 強制イベントの中で、未読のものがあったら次のフレームで、強制的にノベルのシーンに飛ばします。
                 */
                if ( !visit )
                {
                    value[u8"visit"] = true;
                    Json::StyledWriter writer;
                    writeUserLocal( writer.write( root ), save_name );
                    scheduleOnce( [ = ] ( float d ) { SceneManager::createNovel( scenario ); }, 0.016F, std::string( u8"scene" ) );
                    return;
                }
            }

            /**
             * 貼り付けるための背景を作成します。
             */
            auto map = root[island_name][u8"background"].asString( );
            auto background = CityMap::create( )->make( map );
            background->setName( u8"background" );
            addChild( background, -1 );

            /**
             * メインシナリオを読み込んで貼り付けていきます。
             */
            for ( auto& value : root[island_name][u8"point.main"] )
            {
                ScenarioPointData data;
                data.scenario = value[u8"scenario"].asString( );
                data.visit = value[u8"visit"].asBool( );
                data.position = Vec2( value[u8"position"][0].asInt( ),
                                      value[u8"position"][1].asInt( ) );

                auto mark = MainMark::create( );
                mark->pasteMap( background, data );

                mark->setButtonEndCallBack( [ this, &value ]
                {
                    if ( auto sprite = Sprite::create( ) )
                    {
                        sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                        sprite->setAnchorPoint( Vec2( 0, 0 ) );
                        sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                        sprite->setOpacity( 0 );
                        sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this, &value ] 
                        {
                            value[u8"visit"] = true;
                            Json::StyledWriter writer;
                            writeUserLocal( writer.write( root ), save_name );
                            SceneManager::createNovel( value[u8"scenario"].asString( ) ); 
                        } ), RemoveSelf::create( ), nullptr ) );
                        addChild( sprite );
                    }
                } );
            }

            /**
             * サブシナリオを読み込んで貼り付けていきます。
             */
            for ( auto& value : root[island_name][u8"point.sub"] )
            {
                ScenarioPointData data;
                data.scenario = value[u8"scenario"].asString( );
                data.visit = value[u8"visit"].asBool( );
                data.position = Vec2( value[u8"position"][0].asInt( ),
                                      value[u8"position"][1].asInt( ) );

                auto mark = SubMark::create( );
                mark->pasteMap( background, data );

                mark->setButtonEndCallBack( [ this, &value ]
                {
                    if ( auto sprite = Sprite::create( ) )
                    {
                        sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                        sprite->setAnchorPoint( Vec2( 0, 0 ) );
                        sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                        sprite->setOpacity( 0 );
                        sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this, &value ]
                        {
                            value[u8"visit"] = true;
                            Json::StyledWriter writer;
                            writeUserLocal( writer.write( root ), save_name );
                            SceneManager::createNovel( value[u8"scenario"].asString( ) );
                        } ), RemoveSelf::create( ), nullptr ) );
                        addChild( sprite );
                    }
                } );
            }
        }
    }
    cocos2d::Label * LayerCity::createLabel( std::string const& title )
    {
        auto font = Label::createWithTTF( title,
                                          u8"res/fonts/HGRGE.TTC",
                                          64 );
        font->setAnchorPoint( Vec2( 0.5F, 0 ) );
        font->setAnchorPoint( Vec2( 0, 0 ) );
        font->setTextColor( Color4B( 39, 39, 39, 255 ) );
        return font;
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
