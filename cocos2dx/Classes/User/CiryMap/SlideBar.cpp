#include "LayerOption.h"

USING_NS_CC;

namespace User
{
    SlideBar::SlideBar( float t )
        : SlideBar( )
    {
        slider->setPercent( t * 100 );
    }
    SlideBar::SlideBar( std::string key )
        : SlideBar( )
    {
        this->key = key;

        auto value = UserDefault::getInstance( )->getFloatForKey( key.c_str( ) );
        slider->setPercent( value * 100.0F );
    }
}
