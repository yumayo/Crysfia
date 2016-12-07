#include "LayerCity.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include <vector>
#include <functional>

#include "../Novel/ScriptHeart.h"

USING_NS_CC;

namespace User
{
    void Mark::pasteMap( cocos2d::Sprite * map, ScenarioPointData const & data )
    {
        initData( data );

        auto s = map->getContentSize( );

        float x = position.x;
        float y = position.y;

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

        x *= scale; y *= scale;

        map->addChild( this );

        setPosition( Vec2( x, s.height - y ) );
        auto tar = Size( 64, 64 );
        auto con = getContentSize( );
        auto sca = tar.height / con.height;
        setScale( sca, sca );

        addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( auto parent = getParent( ) )
                {
                    if ( auto p = dynamic_cast<CityMap*>( parent ) )
                        p->allChildCheckRemoved( );
                }

                const std::string dir = u8"res/texture/system/";

                auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

                auto kuroe = Sprite::create( dir + "kuroeicon.png" );
                addChild( kuroe );
                kuroe->setPosition( Vec2( getContentSize( ) / 2 ) );

                auto ok = ui::Button::create( dir + u8"ok.png" );
                addChild( ok );
                ok->setPosition( Vec2( getContentSize( ) / 2 ) + Vec2( 0, -64 - 128 - 35 ) * scale );
                ok->addTouchEventListener( [ map, this ] ( Ref* pSender, ui::Widget::TouchEventType type )
                {
                    if ( type == ui::Widget::TouchEventType::ENDED )
                    {
                        map->pause( );
                        SceneManager::createNovel( this->scenario );
                    }
                } );
            }
        } );
    }

    void MainMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.main.png" );

        Mark::pasteMap( map, data );
    }

    void SubMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.sub.png" );

        Mark::pasteMap( map, data );
    }

    Calendar* Calendar::make( int day )
    {
        const std::string dir = u8"res/texture/system/";

        initWithFile( dir + "calendar.png" );

        setAnchorPoint( Vec2( 1, 1 ) );

        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto size = Director::getInstance( )->getVisibleSize( );
        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

        auto tar = Size( 196, 196 );
        auto con = getContentSize( );
        auto sca = tar.height / con.height;
        setScale( sca, sca );
        auto pos = size;
        setPosition( origin + pos );

        this->day = day;

        auto fDay = Label::createWithTTF( StringUtils::toString( day ),
                                          u8"res/fonts/meiryo.ttc",
                                          150 );
        this->addChild( fDay );
        fDay->setPosition( 128 * scale, ( con.height - 256 ) * scale );
        fDay->setColor( Color3B( 39, 39, 39 ) );

        return this;
    }

    CityMap* CityMap::make( std::string const& backgroundfile )
    {
        const std::string dir = u8"res/texture/system/";

        initWithFile( dir + backgroundfile );

        auto size = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto targetSize = size;
        translate = origin + size / 2;
        backgroundWindowHeightFitScale = targetSize.height / getContentSize( ).height;

        setPosition( translate );
        setScale( backgroundWindowHeightFitScale, backgroundWindowHeightFitScale );

        auto listener = EventListenerTouchAllAtOnce::create( );
        listener->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {

        };
        listener->onTouchesMoved = [ this ] ( const std::vector<Touch*>& touches, Event* event )
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

    void CityMap::allChildCheckRemoved( )
    {
        for ( auto& obj : getChildren( ) )
        {
            obj->removeAllChildren( );
        }
    }

    LayerCity::LayerCity( std::string const& backgroundPath )
        : backgroundPath( backgroundPath )
    {

    }
    LayerCity::~LayerCity( )
    {
    }
    bool LayerCity::init( )
    {
        if ( !Layer::init( ) ) return false;

        auto background = CityMap::create( )->make( backgroundPath );
        this->addChild( background );

        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 155, 384 ), u8"scenario1.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 167, 201 ), u8"scenario2.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 342, 102 ), u8"scenario3.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 374, 248 ), u8"scenario4.txt" } );
        SubMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 256, 256 ), u8"live2d.txt" } );

        this->addChild( Calendar::create( )->make( 5 ) );

        this->addChild( createBackButton( ) );

        this->addChild( HeartGauge::create( )->make( ) );

        return true;
    }
    void LayerCity::setup( )
    {

    }
    cocos2d::ui::Button * LayerCity::createBackButton( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );

        auto tar = Size( 128, 128 );
        auto con = button->getContentSize( );
        auto sca = tar.height / con.height;
        button->setScale( sca, sca );
        button->setPosition( origin + tar / 2.0 );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                SceneManager::createBreeding( );
            }
        } );
        return button;
    }
}
