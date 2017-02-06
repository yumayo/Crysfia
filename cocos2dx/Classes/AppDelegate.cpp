#include "AppDelegate.h"
#include "Lib/EnvironmentDefaultData/EnvironmentDefaultData.h"
#include "User/SceneManager.h"
#include "User/System/DataSettings.h"

USING_NS_CC;

AppDelegate::AppDelegate( )
{

}

AppDelegate::~AppDelegate( )
{

}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs( )
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

    GLView::setGLContextAttrs( glContextAttrs );
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages( )
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching( ) {

    auto env = Env::getInstance( );

    auto size = Size( 1080, 1920 ) * 0.5;

    // initialize director
    auto director = Director::getInstance( );
    auto glview = director->getOpenGLView( );
    if ( !glview ) {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect( env->gameName, cocos2d::Rect( 0, 0, size.width, size.height ) );
    #else
        glview = GLViewImpl::create( env->gameName );
    #endif
        director->setOpenGLView( glview );
    }

#ifdef _DEBUG
    // turn on display FPS
    director->setDisplayStats( true );
#endif // _DEBUG

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval( 1.0f / 60 );

    // Set the design resolution
    glview->setDesignResolutionSize( env->designResolutionSize.width, env->designResolutionSize.height, ResolutionPolicy::SHOW_ALL );

    auto frameSize = glview->getFrameSize( );

    auto aspectRatio = frameSize.width / frameSize.height;

    const float AR_1_2 = 1.0F / 2.0F;
    const float AR_9_16 = 9.0F / 16.0F;
    const float AR_10_16 = 10.0F / 16.0F;
    const float AR_2_3 = 2.0F / 3.0F;
    const float AR_3_4 = 3.0F / 4.0F;
    const float AR_1_1 = 1.0F / 1.0F;
    const float AR_4_3 = 4.0F / 3.0F;
    const float AR_3_2 = 3.0F / 2.0F;
    const float AR_16_10 = 16.0F / 10.0F;
    const float AR_16_9 = 16.0F / 9.0F;
    const float AR_2_1 = 2.0F / 1.0F;

    std::string ar;

    if ( aspectRatio <= AR_1_2 )
    {
        ar = u8"AR_1_2";
    }
    else if ( aspectRatio <= AR_9_16 )
    {
        ar = u8"AR_9_16";
    }
    else if ( aspectRatio <= AR_10_16 )
    {
        ar = u8"AR_10_16";
    }
    else if ( aspectRatio <= AR_2_3 )
    {
        ar = u8"AR_2_3";
    }
    else if ( aspectRatio <= AR_3_4 )
    {
        ar = u8"AR_3_4";
    }
    else if ( aspectRatio <= AR_1_1 )
    {
        ar = u8"AR_1_1";
    }
    else if ( aspectRatio <= AR_4_3 )
    {
        ar = u8"AR_4_3";
    }
    else if ( aspectRatio <= AR_3_2 )
    {
        ar = u8"AR_3_2";
    }
    else if ( aspectRatio <= AR_16_10 )
    {
        ar = u8"AR_16_10";
    }
    else if ( aspectRatio <= AR_16_9 )
    {
        ar = u8"AR_16_9";
    }
    else if ( aspectRatio <= AR_2_1 )
    {
        ar = u8"AR_2_1";
    }
    else
    {
        ar = u8"none";
    }

    // if the frame's height is larger than the height of medium size.
    if ( frameSize.height > env->mediumResolutionSize.height )
    {
        director->setContentScaleFactor( MIN( env->largeResolutionSize.height / env->designResolutionSize.height, env->largeResolutionSize.width / env->designResolutionSize.width ) );
    }
    // if the frame's height is larger than the height of small size.
    else if ( frameSize.height > env->smallResolutionSize.height )
    {
        director->setContentScaleFactor( MIN( env->mediumResolutionSize.height / env->designResolutionSize.height, env->mediumResolutionSize.width / env->designResolutionSize.width ) );
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor( MIN( env->smallResolutionSize.height / env->designResolutionSize.height, env->smallResolutionSize.width / env->designResolutionSize.width ) );
    }

    register_all_packages( );

    User::userDefaultSetup( );

    User::SceneManager::createSystemAppDelegateStart( );

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground( ) {
    Director::getInstance( )->stopAnimation( );

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground( ) {
    Director::getInstance( )->startAnimation( );

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
