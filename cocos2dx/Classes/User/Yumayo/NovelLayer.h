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
    public:
        void setNextChild( std::string const& name );
        void textUpdate( );
    private:
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
