#include "NameLayer.h"

#include "OptionalValues.h"

USING_NS_CC;

namespace User
{
    NameLayer::NameLayer( )
    {

    }
    NameLayer::~NameLayer( )
    {

    }
    bool NameLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        return true;
    }
    void NameLayer::setup( )
    {

    }
    void NameLayer::on( )
    {
        this->setVisible( true );
    }
    void NameLayer::off( )
    {
        this->setVisible( false );
    }
}
