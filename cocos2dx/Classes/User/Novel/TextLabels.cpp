#include "TextLabels.h"

#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    TextLabels::TextLabels( cocos2d::Layer * layer )
        : textStrings( { layer, layer, layer } )
    {

    }
    TextLabels::~TextLabels( )
    {

    }
    void TextLabels::clear( )
    {
        isReadOuted = false;
    }
    void TextLabels::setStrings( NovelData const & strings, cocos2d::Vec2 position )
    {
        for ( auto& ds : textStrings ) ds.layerPeelOff( );

        auto& ds = textStrings;

        for ( size_t i = 0, size = ds.size( ); i < size; ++i )
        {
            ds[i].setLabelString( strings[i] );
            ds[i].setDrawPosition( Vec2( position.x, position.y - OptionalValues::lineViewSize * i ) );
        }

        ds[0].actionAndCallfuncStart( [ & ] { ds[1].actionAndCallfuncStart( [ & ] { ds[2].actionAndCallfuncStart( [ this ] { isReadOuted = true; if ( animationEndCallBack ) animationEndCallBack( ); } ); } ); } );

        for ( auto& ds : textStrings ) ds.layerPasting( );
    }
    void TextLabels::actionStop( )
    {
        for ( auto& obj : textStrings ) obj.actionStop( );
        if ( !isReadOuted ) if ( animationEndCallBack ) animationEndCallBack( );
        isReadOuted = true;
    }
    bool TextLabels::getIsReadOuted( )
    {
        return isReadOuted;
    }
}
