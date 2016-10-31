#include "LayerIsland.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    LayerIsland::LayerIsland( )
    {

    }
    LayerIsland::~LayerIsland( )
    {

    }
    //ブロックオブジェクト作成  
    /*LayerColor * LayerIsland::createBlockLayer( const char *strlabel, Color3B fontColor, Color4B backColor )
    {
        LayerColor * ret = LayerColor::create( backColor, 128, 128 );
        CCLabelTTF *Label = CCLabelTTF::create( strlabel, "Arial-BoldMT", 28, CCSizeMake( 128, 128 ), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter );
        Label->setColor( fontColor );
        Label->setAnchorPoint( CCPointZero );
        ret->addChild( Label );
        return ret;
    }*/

    bool LayerIsland::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"LayerIsland", "res/fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        this->scheduleUpdate( );

        ////メニューボタンオブジェ作成  
        //Array *menuItems = Array::create( );

        ////STAGE  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "STARGE", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0xFF ) ) ) );
        ////オクトパス  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "オクトパス", ccc3( 0xFF, 0x7F, 0x7F ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////ペンギン  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "ペンギン", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////MAP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "MAP", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );
        ////アルマジロ  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "アルマジロ", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////NOP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        ////エレファント  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "エレファント", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////ファルコン  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "ファルコン", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////NOP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        ////クワガタ  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "クワガタ", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////SPEC  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "SPEC", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );
        ////マントヒヒ  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "マントヒヒ", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////カメレオン  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "カメレオン", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////WONDER  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "WONDER", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );

        //Menu *menu = Menu::createWithArray( menuItems );
        //this->addChild( menu );

        ////ボタンを横に整頓する  
        //menu->alignItemsHorizontallyWithPadding( 0 );

        ////ボタンを縦に整頓する  
        //menu->alignItemsVerticallyWithPadding( 0 );

        ////配置  
        //menu->alignItemsInColumns( 4, 4, 4, 4 );

        return true;
    }
    void LayerIsland::setup( )
    {
        
    }
    void LayerIsland::update( float delta )
    {
        SceneManager::createYumayo( );
    }
}
