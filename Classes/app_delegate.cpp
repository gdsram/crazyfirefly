#include "app_delegate.h"

#include "audio/include/SimpleAudioEngine.h"

#include "app_macros.h"
#include "scenes/main_menu_scene.h"

/*
//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}
*/

bool AppDelegate::applicationDidFinishLaunching() {

    // initialize director
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) {
        glview = cocos2d::GLViewImpl::create("Crazy Firefly");
        director->setOpenGLView(glview);
    }

    director->setContentScaleFactor( 1080 / designResolutionSize.width);

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);

    // add sprite frame
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet1.plist", "sprite_sheet1.png");

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto tScene = MainMenuScene::createScene();

    // run
	director->runWithScene(tScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    cocos2d::Director::getInstance()->stopAnimation();
	// stopping audio
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    cocos2d::Director::getInstance()->startAnimation();
	// resuming audio
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
