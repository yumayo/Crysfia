#include "FlickFunctionLayer.h"

#include "NovelLayer.h"

#include "BackLogLayer.h"

#include "NameLayer.h"

#include "ScriptStaticData.h"

#include "../SceneManager.h"

#include "ScriptSystem.h"

#include "../TouchiEvent/EventListenerGesture.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    Functions::Functions( std::vector<std::pair<std::string, std::function<void( )>>> functions )
    {
        const auto vo = Director::getInstance( )->getVisibleOrigin( );
        const auto vs = Director::getInstance( )->getVisibleSize( );

        auto width = vs.width;
        icon_size = width / functions.size( );
        auto tartgetSize = Vec2( icon_size, icon_size );

        setContentSize( Size( width, icon_size ) );
        setAnchorPoint( Vec2( 0, 0 ) );
        setPosition( Vec2( 0, -icon_size ) );
        setName( u8"functions" );

        for ( int i = 0, is = functions.size( ); i < is; ++i )
        {
            const auto vo = Director::getInstance( )->getVisibleOrigin( );
            const auto vs = Director::getInstance( )->getVisibleSize( );
            auto button = ui::Button::create( u8"res/texture/system/icon." + functions[i].first + u8".png",
                                              u8"res/texture/system/icon." + functions[i].first + u8".select.png" );
            button->setName( functions[i].first );
            button->setAnchorPoint( Vec2( 0, 0 ) );
            button->setPosition( vo + Vec2( icon_size * i, 0 ) );
            button->setScale( Lib::fitWidth( button, icon_size ) );

            button->addTouchEventListener( [ this, functions, i ] ( LAMBDA_TOUCH )
            {
                switch ( type )
                {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    break;
                case cocos2d::ui::Widget::TouchEventType::MOVED:
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    functions[i].second( );
                    end( );
                    break;
                case cocos2d::ui::Widget::TouchEventType::CANCELED:
                    break;
                default:
                    break;
                }
            } );
            addChild( button );
        }
    }
    void Functions::begin( )
    {
        runAction( EaseExponentialOut::create( MoveTo::create( 0.3F, Vec2( 0, 0 ) ) ) );
    }
    void Functions::cancel( )
    {
        runAction( Sequence::create( EaseExponentialOut::create( MoveTo::create( 0.3F, Vec2( 0, -icon_size ) ) ), CallFunc::create( canceled ), RemoveSelf::create( ), nullptr ) );
    }
    void Functions::end( )
    {
        runAction( Sequence::create( EaseExponentialOut::create( MoveTo::create( 0.3F, Vec2( 0, -icon_size ) ) ), CallFunc::create( ended ), RemoveSelf::create( ), nullptr ) );
    }
    FlickFunctionLayer::FlickFunctionLayer( )
    {


    }
    FlickFunctionLayer::~FlickFunctionLayer( )
    {

    }
    bool FlickFunctionLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        auto touch = EventListenerGesture::create( );
        touch->onTap = [ this ] ( Vec2 pos )
        {
            bool hit = false;
            enumerateChildren( "//.*", [ pos, &hit ] ( cocos2d::Node* node )
            {
                hit = hit || node->getBoundingBox( ).containsPoint( pos );
                return hit;
            } );
            if ( !hit )
            {
                if ( functions )
                {
                    functions->cancel( );
                }
            }
        };
        touch->onSwipe = [ this ] ( EventListenerGesture::SwipeDirection direction )
        {
            switch ( direction )
            {
            case EventListenerGesture::SwipeDirection::NONE:
                break;
            case EventListenerGesture::SwipeDirection::UP:
                /**
                 * スワイプが上方向にされたときのみ、メニューを表示させる。
                 * すでに表示されている場合は表示しない。
                 */

                if ( !functions )
                {
                    createFlickCircle( );
                }
                break;
            case EventListenerGesture::SwipeDirection::DOWN:
                break;
            case EventListenerGesture::SwipeDirection::LEFT:
                break;
            case EventListenerGesture::SwipeDirection::RIGHT:
                break;
            default:
                break;
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touch, this );

        return true;
    }
    void FlickFunctionLayer::setup( )
    {
        backlogLayer = getLayer<BackLogLayer>( );
        novelLayer = getLayer<NovelLayer>( );
        nameLayer = getLayer<NameLayer>( );
    }
    void FlickFunctionLayer::end( )
    {
        if ( functions ) functions->end( );
    }
    void FlickFunctionLayer::createFlickCircle( )
    {
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->stop( );

        std::vector<std::pair<std::string, std::function<void( )>>> args;
        args.emplace_back( std::make_pair( "auto", [ this ]
        {
            if ( auto layer = dynamic_cast<NovelLayer*>( novelLayer ) )
            {
                layer->addAuto( );
                scheduleOnce( [ this ] ( float delay )
                {
                    novelLayer->resume( );
                }, 0.0F, typeid( this ).name( ) );
            }
        } ) );
        args.emplace_back( std::make_pair( "skip", [ this ]
        {
            if ( auto layer = dynamic_cast<NovelLayer*>( novelLayer ) )
            {
                layer->skip( );
                scheduleOnce( [ this ] ( float delay )
                {
                    novelLayer->resume( );
                }, 0.0F, typeid( this ).name( ) );
            }
        } ) );
        args.emplace_back( std::make_pair( "log", [ this ]
        {
            if ( auto layer = dynamic_cast<BackLogLayer*>( backlogLayer ) )
            {
                layer->showBacklog( );
            }
        } ) );
        args.emplace_back( std::make_pair( "window", [ this ]
        {
            if ( auto layer = dynamic_cast<NameLayer*>( nameLayer ) )
            {
                layer->addNovelWinodowSwitch( );
            }
        } ) );

        functions = Functions::create( args );
        functions->begin( );
        functions->ended = [ this ] { functions = nullptr; };
        functions->canceled = [ this ]
        {
            functions = nullptr;
            if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->restart( );
        };
        addChild( functions );
    }
}
