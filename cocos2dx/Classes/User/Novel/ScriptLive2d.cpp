//#include "ScriptLive2d.h"
//
//USING_NS_CC;
//
//namespace User
//{
//    ScriptLive2d::ScriptLive2d( cocos2d::Layer* layer, std::string dirPath, std::string jsonPath )
//        : ScriptBase( layer )
//        , dirPath( dirPath )
//        , jsonPath( jsonPath )
//    {
//        funcs.insert( std::make_pair( u8"in", [ this ] ( ArgumentList const& args ) { in( args ); } ) );
//        funcs.insert( std::make_pair( u8"out", [ this ] ( ArgumentList const& args ) { out( args ); } ) );
//        funcs.insert( std::make_pair( u8"fadein", [ this ] ( ArgumentList const& args ) { fadein( args ); } ) );
//        funcs.insert( std::make_pair( u8"fadeout", [ this ] ( ArgumentList const& args ) { fadeout( args ); } ) );
//    }
//    ScriptLive2d::~ScriptLive2d( )
//    {
//
//    }
//    void ScriptLive2d::in( ArgumentList const& args )
//    {
//        create( );
//    }
//    void ScriptLive2d::out( ArgumentList const & args )
//    {
//        layer->removeChildByTag( (int)Tag::Human );
//    }
//    void ScriptLive2d::fadein( ArgumentList const & args )
//    {
//        auto sprite = create( );
//        if ( !sprite ) return;
//
//        sprite->setOpacity( 0 );
//
//        auto fade = FadeIn::create( 1.0 );
//        sprite->runAction( Sequence::create( fade, nullptr ) );
//    }
//    void ScriptLive2d::fadeout( ArgumentList const & args )
//    {
//        if ( auto node = layer->getChildByTag( (int)Tag::Human ) )
//        {
//            auto fade = FadeOut::create( 1.0 );
//            auto remove = RemoveSelf::create( );
//            node->runAction( Sequence::create( fade, remove, nullptr ) );
//        }
//    }
//    cocos2d::Sprite * ScriptLive2d::create( )
//    {
//        layer->removeChildByTag( (int)Tag::Live2d );
//        auto visibleSize = Director::getInstance( )->getVisibleSize( );
//        auto origin = Director::getInstance( )->getVisibleOrigin( );
//
//        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
//        if ( !sprite ) return nullptr;
//
//        sprite->setTag( (int)Tag::Live2d );
//        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
//                                            visibleSize.height / 2 ) );
//
//        auto size = sprite->getContentSize( );
//        auto targetSize = Size( visibleSize );
//        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );
//        layer->addChild( sprite );
//
//        return sprite;
//    }
//}
