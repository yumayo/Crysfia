#include "TemporaryCharacter.h"

#include "../Live2d/LAppView.h"
#include "../Live2d/LAppLive2DManager.h"
#include "../Live2d/LAppDefine.h"

USING_NS_CC;

namespace User
{
    bool TemporaryCharacter::init( )
    {
        if ( !Layer::init( ) ) { return false; }

        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        auto _scale = 1.0F / scale;


        scheduleOnce( [ this ] ( float y )
        {
            auto index = UserDefault::getInstance( )->getIntegerForKey( u8"現在の服" );
            std::string model = u8"crysfia";

            std::vector<std::string> names =
            {
                u8"_d",//u8"ワンピース"
                u8"_d",//u8"ドレス",
                u8"_d",//u8"着ぐるみ",
                u8"_d",//u8"シスター服",
                u8"_s",//u8"セーラー服"
            };
            model += names[index];
            auto dir = u8"res/live2d/" + model + u8"/";

            auto manager = LAppLive2DManager::getInstance( );


            manager->createModel( dir, model + u8".model.json" );

            auto live2d = LAppView::createDrawNode( );
            addChild( live2d, 0 );
        }, 0.0F, u8"fia_delay" );

        // ここからマスクの処理を書きます。
        if ( auto clipping = ClippingNode::create( ) )
        {
            // クリッピングノードはゲージの子供とします。
            addChild( clipping, 1 );
            // ただしそのときに、原点を合わせるため以下の数値を代入しておきます。
            clipping->setPosition( vo + vs * 0.5F );
            clipping->setScale( scale );

            // 実際に書き込むのは色のある部分です。
            clipping->setInverted( false );
            // 透明部分をマスクします。
            clipping->setAlphaThreshold( 0.0 );

            // マスク画像を用意します。
            if ( auto mask = Sprite::create( u8"res/texture/home/bottle_mask.png" ) )
            {
                clipping->setStencil( mask );
            }

            // 塗りつぶすイメージを用意します。
            if ( auto background = Sprite::create( u8"res/texture/home/water.png" ) )
            {
                // なぜがグリッドがうまくいかない
                //auto wave = Waves3D::create( 10, Size( 9, 16 ), 18, 15 );
                //auto grid = NodeGrid::create( );
                //grid->addChild( background );
                //grid->runAction( RepeatForever::create( wave ) );

                // 仕方がないので、そのままaddします。
                clipping->addChild( background );

                background->setOpacity( 64 );
            }
        }

        if ( auto clipping = ClippingNode::create( ) )
        {
            // クリッピングノードはゲージの子供とします。
            addChild( clipping, 2 );
            // ただしそのときに、原点を合わせるため以下の数値を代入しておきます。
            clipping->setPosition( vo + vs * 0.5F );
            clipping->setScale( scale );

            // 実際に書き込むのは色のある部分です。
            clipping->setInverted( false );
            // 透明部分をマスクします。
            clipping->setAlphaThreshold( 0.0 );

            // マスク画像を用意します。
            if ( auto mask = Sprite::create( u8"res/texture/home/bottle_mask.png" ) )
            {
                clipping->setStencil( mask );
            }

            // 泡を生成します。
            auto spawn_bubble = CallFunc::create( [ this, vs, clipping ]
            {
                auto p = RandomHelper::random_int( 1, 6 );
                std::string name = u8"awa" + StringUtils::toString( p ) + u8".png";
                auto bubble = Sprite::create( u8"res/texture/home/" + name );

                auto x = RandomHelper::random_real( -vs.width*0.5F, vs.width * 0.5F );
                auto y = -vs.height * 0.5 - bubble->getContentSize( ).height;
                auto tar_y = vs.height + bubble->getContentSize( ).height * 2;
                bubble->setPosition( Vec2( x, y ) );
                bubble->setOpacity( 128 );

                auto time = RandomHelper::random_real( 3.0F, 6.0F );
                auto wave = Spawn::create( ActionFloat::create( time, 0.0F, 30.0F, [ bubble, x ] ( float val ) { bubble->setPosition( sin( val ) * 20 + x, bubble->getPosition( ).y ); } ),
                                           ActionFloat::create( time, y, tar_y, [ bubble ] ( float val ) { bubble->setPosition( bubble->getPosition( ).x, val ); } ),
                                           nullptr );
                bubble->runAction( Sequence::create( wave, RemoveSelf::create( ), nullptr ) );
                clipping->addChild( bubble );
            } );

            auto spawner = Node::create( );
            addChild( spawner, 3 );
            spawner->runAction( RepeatForever::create( Sequence::create( spawn_bubble, DelayTime::create( 2.0F ), nullptr ) ) );
        }

        auto bottle = Sprite::create( u8"res/texture/home/bottle_1.png" );
        bottle->setPosition( vo + vs * 0.5F );
        bottle->setScale( scale );
        addChild( bottle, 4 );

        return true;
    }
}
