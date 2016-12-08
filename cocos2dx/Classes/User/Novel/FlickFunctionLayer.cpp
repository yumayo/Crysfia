#include "FlickFunctionLayer.h"

#include "NovelLayer.h"

#include "BackLogLayer.h"

#include "ScriptStaticData.h"

#include "../SceneManager.h"

#include "ScriptSystem.h"

USING_NS_CC;

namespace User
{
    int Menu::maxMenuNumber = 0;
    float Menu::circleRadius = 0.0F;

    void Menu::update( bool touch )
    {
        prevOnTouch = onTouch;
        onTouch = touch;

        const std::string dir = u8"res/texture/system/";

        if ( isIn( ) )
        {
            initWithFile( dir + u8"base.true.png" );
        }
        else if ( isStay( ) )
        {
            if ( auto parent = getParent( ) )
            {
                parent->setName( getName( ) );
            }
        }
        else if ( isOut( ) )
        {
            if ( auto parent = getParent( ) )
            {
                parent->setName( "" );
            }
            initWithFile( dir + u8"base.false.png" );
        }
    }
    bool Menu::isHit( cocos2d::Vec2 touchPos )
    {
        auto pos = convertToWorldSpaceAR( cocos2d::Point::ZERO );

        return pos.distance( touchPos ) < circleRadius;
    }
    bool Menu::isIn( )
    {
        return !prevOnTouch && onTouch;
    }
    bool Menu::isStay( )
    {
        return prevOnTouch && onTouch;
    }
    bool Menu::isOut( )
    {
        return prevOnTouch && !onTouch;
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

        this->scheduleUpdate( );

        auto multiTouchEvent = EventListenerTouchAllAtOnce::create( );
        multiTouchEvent->onTouchesBegan = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                began( touch );
            }
        };
        multiTouchEvent->onTouchesMoved = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                moved( touch );
            }
        };
        multiTouchEvent->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                ended( touch );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( multiTouchEvent, this );



        return true;
    }
    void FlickFunctionLayer::setup( )
    {
        baglogLayer = getLayer<BackLogLayer>( );
        novelLayer = getLayer<NovelLayer>( );
    }
    void FlickFunctionLayer::update( float delta )
    {
        if ( isTap && !isLongTap( ) ) holdTapTime += delta;

        if ( isLongTap( ) && !circle ) createFlickCircle( );

        if ( isFunction )
        {
            if ( circle )
            {
                for ( auto& obj : circle->getChildren( ) )
                {
                    if ( auto item = dynamic_cast<Menu*>( obj ) )
                    {
                        item->update( item->isHit( tapLastPosition ) );
                    }
                }
            }
        }
    }
    void FlickFunctionLayer::began( cocos2d::Touch * touch )
    {
        isTap = true;

        isFunction = false;

        isSuccessLongTap = true;

        holdTapTime = 0.0F;

        tapBeganPosition = touch->getLocation( );

        tapLastPosition = tapBeganPosition;
    }
    void FlickFunctionLayer::moved( cocos2d::Touch * touch )
    {
        tapLastPosition = touch->getLocation( );

        if ( !isLongTap( ) )
        {
            if ( longTapShiftLength <= tapBeganPosition.distance( tapLastPosition ) ) isSuccessLongTap = false;
        }
    }
    void FlickFunctionLayer::ended( cocos2d::Touch * touch )
    {
        isTap = false;
        isFunction = false;

        // ‹@”\‚Ì‚·‚×‚Ä‚ð‚µ‚Ü‚¤
        if ( circle )
        {
            if ( novelLayer ) novelLayer->resume( );

            auto children = circle->getChildren( );
            int i = 0;
            for ( int size = children.size( ); i < size; ++i )
            {
                auto move = MoveTo::create( 1.0F, Vec2::ZERO );
                auto easing = EaseExponentialOut::create( move );
                children.at( i )->stopAllActions( );
                children.at( i )->runAction( Sequence::create( easing, nullptr ) );
            }

            auto scale = ScaleTo::create( 1.0F, 0.0F );
            auto easeScale = EaseElasticOut::create( scale );
            auto modeShift = CallFunc::create( [ this ]
            {
                if ( !circle->getName( ).empty( ) )
                    if ( auto item = dynamic_cast<Menu*>( circle->getChildByName( circle->getName( ) ) ) )
                    {
                        item->menuCallBack( );
                    }
            } );
            circle->stopAllActions( );
            circle->runAction( Sequence::create( modeShift, easeScale, RemoveSelf::create( ), CallFunc::create( [ this ] { circle = nullptr; } ), nullptr ) );
        }
    }
    void FlickFunctionLayer::createFlickCircle( )
    {
        if ( novelLayer ) novelLayer->pause( );

        Menu::maxMenuNumber = numberMenu;
        Menu::circleRadius = menuCircleRadius;

        // ’†‰›‚ÌŠÛ
        circle = Node::create( );
        this->addChild( circle );
        circle->setPosition( tapLastPosition );
        circle->setScale( 0.0F );
        auto scale = ScaleTo::create( 1.0F, 1.0F );
        auto easing = EaseElasticOut::create( scale );
        circle->runAction( Sequence::create( easing, DelayTime::create( longTapShiftTime ), CallFunc::create( [ this ] { isFunction = true; } ), nullptr ) );

        addMenu( "backlog", [ this ]
        {
            if ( auto baglog = dynamic_cast<BackLogLayer*>( baglogLayer ) )
            {
                baglog->showBacklog( );
            }
        } );
        addMenu( "novelswitch", [ this ]
        {
            ScriptStaticData::run( { "sys", "novelswitch" } );
        } );
        addMenu( "save", [ this ]
        {

        } );
        addMenu( "load", [ this ]
        {

        } );
    }
    void FlickFunctionLayer::addMenu( std::string name, std::function<void( )> const & lambda )
    {
        const std::string dir = u8"res/texture/system/";
        const float selfAngle = M_PI * 2 / Menu::maxMenuNumber;

        auto menu = Menu::create( );
        menu->initWithFile( dir + u8"base.false.png" );
        circle->addChild( menu );
        menu->menuCallBack = lambda;
        menu->setName( name );
        auto move = MoveTo::create( 1.0F, Vec2( cos( selfAngle * circle->getChildrenCount( ) ) * ( menuLength + Menu::circleRadius ),
                                                sin( selfAngle * circle->getChildrenCount( ) ) * ( menuLength + Menu::circleRadius ) ) );
        auto easing = EaseExponentialOut::create( move );
        menu->runAction( Sequence::create( easing, nullptr ) );

        auto icon = Sprite::create( dir + name + u8".png" );
        menu->addChild( icon );
        icon->setAnchorPoint( Vec2( 0, 0 ) );
    }
}