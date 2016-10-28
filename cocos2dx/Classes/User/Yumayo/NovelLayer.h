# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class NovelLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NovelLayer );
        NovelLayer( );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void setNextChild( std::string const& name );
        void textUpdate( );
        void switchIsNextText( ) { isNextText = !isNextText; }
    private:
        bool isNextText = true;
        bool isReadingProceed = false;
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
