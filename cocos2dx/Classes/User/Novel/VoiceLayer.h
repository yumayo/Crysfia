# ifndef __VoiceLayer__
# define __VoiceLayer__

# include "../LayerBase.h"

namespace User
{
    class VoiceLayer : public LayerBase
    {
    public:
        CREATE_FUNC( VoiceLayer );
        VoiceLayer( );
        ~VoiceLayer( );
        bool init( ) override;
        void setup( ) override;
    };
}

# endif // __VoiceLayer__
