#include "FlickFunctionLayer.h"

#include "NovelLayer.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
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
                bool hit = false;
                for ( auto& obj : circle->getChildren( ) )
                {
                    auto item = dynamic_cast<FunctionCircle*>( obj );
                    auto pos = item->getWorldPosition( );

                    float distance;
                    if ( ( distance = pos.distance( tapLastPosition ) ) < subMenuRadius )
                    {
                        log( "distance : %f", distance );
                        circle->drawDot( Vec2::ZERO, circleRadius, item->getDrawColor( ) );
                        hit = true;
                        //break;
                    }
                }
                if ( !hit )
                {
                    circle->drawDot( Vec2::ZERO, circleRadius, Color4F::YELLOW );
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

        // 機能のすべてをしまう
        if ( circle )
        {
            if ( novelLayer ) novelLayer->resume( );

            auto children = circle->getChildren( );
            int i = 0;
            for ( int size = children.size( ); i < size; ++i )
            {
                auto move = MoveTo::create( 1.0F, Vec2::ZERO );
                auto easing = EaseExponentialOut::create( move );
                auto delay = DelayTime::create( 0.1F * i );
                children.at( i )->stopAllActions( );
                children.at( i )->runAction( Sequence::create( delay, easing, nullptr ) );
            }

            auto scale = ScaleTo::create( 1.0F, 0.0F );
            auto easeScale = EaseElasticOut::create( scale );
            auto delay = DelayTime::create( 0.1F * i );
            auto modeShift = CallFunc::create( [ this ] 
            {
                if ( circle->getDrawColor( ) == Color3B::RED )
                {
                    SceneManager::createBreeding( );
                }
                else if ( circle->getDrawColor( ) == Color3B::BLUE )
                {
                    SceneManager::createTitle( );
                }
                else if ( circle->getDrawColor( ) == Color3B::GREEN )
                {
                    SceneManager::createIslandMap( );
                }
            } );
            circle->stopAllActions( );
            circle->runAction( Sequence::create( delay, easeScale, modeShift, RemoveSelf::create( ), CallFunc::create( [ this ] { circle = nullptr; } ), nullptr ) );
        }
    }
    void FlickFunctionLayer::createFlickCircle( )
    {
        if ( novelLayer ) novelLayer->pause( ); 

        // 中央の丸
        int thisNumber = 0;
        circle = FunctionCircle::create( );
        {
            circle->drawDot( Vec2::ZERO, circleRadius, Color4F::YELLOW );
            circle->setPosition( tapLastPosition );
            circle->setScale( 0.0F );
            auto scale = ScaleTo::create( 1.0F, 1.0F );
            auto delay = DelayTime::create( 0.1F * thisNumber );
            auto easing = EaseElasticOut::create( scale );
            circle->runAction( Sequence::create( delay, easing, nullptr ) );
            this->addChild( circle );
        }

        int num = 3;
        float selfAngle = M_PI * 2 / num;

        // セーブ機能
        thisNumber++;
        {
            auto dot = FunctionCircle::create( );
            dot->drawDot( Vec2::ZERO, subMenuRadius, Color4F::RED );
            auto move = MoveTo::create( 1.0F, Vec2( cos( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ), sin( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ) ) );
            auto easing = EaseExponentialOut::create( move );
            auto delay = DelayTime::create( 0.1F * thisNumber );
            dot->runAction( Sequence::create( delay, easing, nullptr ) );
            circle->addChild( dot );
        }

        // ロード機能
        thisNumber++;
        {
            auto dot = FunctionCircle::create( );
            dot->drawDot( Vec2::ZERO, subMenuRadius, Color4F::BLUE );
            auto move = MoveTo::create( 1.0F, Vec2( cos( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ), sin( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ) ) );
            auto easing = EaseExponentialOut::create( move );
            auto delay = DelayTime::create( 0.1F * thisNumber );
            dot->runAction( Sequence::create( delay, easing, nullptr ) );
            circle->addChild( dot );
        }

        // メッセージウィンドウの非表示機能
        thisNumber++;
        {
            auto dot = FunctionCircle::create( );
            dot->drawDot( Vec2::ZERO, subMenuRadius, Color4F::GREEN );
            auto move = MoveTo::create( 1.0F, Vec2( cos( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ), sin( selfAngle * thisNumber ) * ( circleRadius + subMenuRadius ) ) );
            auto easing = EaseExponentialOut::create( move );
            auto delay = DelayTime::create( 0.1F * thisNumber );
            dot->runAction( Sequence::create( delay, easing, CallFunc::create( [ this ] { isFunction = true; } ), nullptr ) );
            circle->addChild( dot );
        }
    }
}