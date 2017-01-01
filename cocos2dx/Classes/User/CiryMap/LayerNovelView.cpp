
#include "LayerNovelView.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    LayerNovelView * LayerNovelView::create( std::string const & title )
    {
        LayerNovelView *pRet = new( std::nothrow ) LayerNovelView( );
        if ( pRet && pRet->init( title ) )
        {
            pRet->autorelease( );
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    bool LayerNovelView::init( std::string const& title )
    {
        if ( !cocos2d::LayerColor::init( ) ) return false;

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        float fadeTime = 0.2F;

        // 色は黒色
        setColor( Color3B::BLACK );

        // 初期状態ではレイヤーは透明。
        setOpacity( 0 );
        // フェードイン
        runAction( FadeTo::create( fadeTime, 32 ) );

        // タップしたら、フェードアウトしてレイヤーを削除する。
        // ダブルタップを防ぐために、一度押されたら、eventを無効にする。
        auto event = EventListenerTouchOneByOne::create( );
        event->setSwallowTouches( true );
        event->onTouchBegan = [this, event, fadeTime]( Touch* t, Event* e )
        {
            for ( auto& child : getChildren( ) )
            {
                child->runAction( FadeOut::create( fadeTime ) );
            }

            auto fade = FadeTo::create( fadeTime, 0 );
            auto remove = RemoveSelf::create( );
            Sequence::create( fade, remove, nullptr );
            return true;
        };
        Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( event, this );

        // 上にタイトル
        // その下にゲットできるアイテムなどを表示
        // 下に決定ボタン

        // タイトル //
        auto titleLabel = Label::createWithTTF( title,
                                                u8"res/fonts/HGRGE.TTC",
                                                32 );
        titleLabel->setAnchorPoint( Vec2( 0.5F, 1.0F ) ); // 真ん中上
        titleLabel->setTextColor( Color4B( 242, 242, 242, 255 ) ); // 白
        titleLabel->setPosition( vo + Vec2( vs.width * 0.5F, vs.height ) ); // 画面真ん中, 上
        addChild( titleLabel );

        // アイテム情報はまだ未定 //

        // 決定ボタン //
        auto okButton = ui::Button::create( u8"res/texture/system/ok.button.png" );
        okButton->setAnchorPoint( Vec2( 0.5F, 0.0F ) );
        okButton->setPosition( vo + Vec2( vs.width * 0.5F, 0.0F ) );
        okButton->addTouchEventListener( [ this, title ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            auto nextScene = CallFunc::create( [ this, title ]
            {
                if ( auto sprite = Sprite::create( ) )
                {
                    sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                    sprite->setAnchorPoint( Vec2( 0, 0 ) );
                    sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                    sprite->setOpacity( 0 );
                    sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this, title ]
                    {
                        SceneManager::createNovel( title );
                    } ), RemoveSelf::create( ), nullptr ) );
                    addChild( sprite );
                }
            } );
            runAction( nextScene );

            // 二度と押せないように。
            pause( );
        } );
        addChild( okButton );

        for ( auto& child : getChildren( ) )
        {
            child->setOpacity( 0 );
            child->runAction( FadeIn::create( fadeTime ) );
        }

        return true;
    }
}
