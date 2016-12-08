#include "LayerCity.h"

#include "../SceneManager.h"

#include "../Novel/OptionalValues.h"

#include <vector>
#include <functional>

#include "../Novel/ScriptHeart.h"

#include "../../Lib/Utility/Utilitys.h"

USING_NS_CC;

namespace User
{
    void Mark::pasteMap( cocos2d::Sprite * map, ScenarioPointData const & data )
    {
        initData( data );

        auto pixel = map->getTexture( )->getContentSizeInPixels( );

        auto scale = 1.0 / Director::getInstance( )->getContentScaleFactor( );

        map->addChild( this );

        setPosition( Vec2( position.x, pixel.height - position.y ) * scale );
        setScale( Lib::fitWidth( this, 64 * scale ), Lib::fitWidth( this, 64 * scale ) );

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
                            map->pause( );
                            SceneManager::createNovel( this->scenario );
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

        Mark::pasteMap( map, data );
    }

    void SubMark::pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data )
    {
        const std::string dir = u8"res/texture/system/";

        loadTextureNormal( dir + "scenario.sub.png" );

        Mark::pasteMap( map, data );
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

            day = UserDefault::getInstance( )->getIntegerForKey( u8"��" );

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
                auto font = Label::createWithTTF( u8"����",
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

        using namespace Lib;

        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto background = CityMap::create( )->make( backgroundPath );
        this->addChild( background );

        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 155, 384 ), u8"scenario1.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 167, 201 ), u8"scenario2.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 342, 102 ), u8"scenario3.txt" } );
        MainMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 374, 248 ), u8"scenario4.txt" } );
        SubMark::create( )->pasteMap( background, { false, cocos2d::Vec2( 256, 256 ), u8"live2d.txt" } );


        /**
         *  ��ʏ㕔�̃��j���[
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
         *  ��ʉ����̃��j���[
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
        }

        return true;
    }
    void LayerCity::setup( )
    {

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
}
