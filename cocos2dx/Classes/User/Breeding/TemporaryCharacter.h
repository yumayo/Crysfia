#pragma once

#include "../LayerBase.h"

namespace User
{
    class TemporaryCharacter : public LayerBase
    {
    public:
        CREATE_FUNC( TemporaryCharacter );
        bool init( );
    private:
    };
}
