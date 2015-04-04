#include "scenes/pause_scene.h"

#include "SimpleAudioEngine.h"

#include "scenes/awards_wall.h"
#include "scenes/game_layer.h"
#include "scenes/main_menu_scene.h"

cocos2d::Scene* PauseScene::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = PauseScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    initMenu();
    initAudio();

    return true;
}

void PauseScene::resume(cocos2d::Ref *pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_pauseSceneAudio);
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	cocos2d::Director::getInstance()->popScene();
}

void PauseScene::goToMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenuScene::createScene();
	cocos2d::Director::getInstance()->popScene();
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void PauseScene::retry(cocos2d::Ref *pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

	auto scene = GameLayer::createScene();
	cocos2d::Director::getInstance()->popScene();
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void PauseScene::goToAwardsWall()
{
    auto scene = AwardsWall::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void PauseScene::initMenu()
{
    auto resumeItem = cocos2d::MenuItemImage::create("buttons/resume.png", "buttons/resume.png", CC_CALLBACK_1(PauseScene::resume, this));
    auto retryItem = cocos2d::MenuItemImage::create("buttons/try again.png", "buttons/try again.png", CC_CALLBACK_1(PauseScene::retry, this));
    auto mainMenuItem = cocos2d::MenuItemImage::create("buttons/main.png", "buttons/main.png", CC_CALLBACK_1(PauseScene::goToMainMenuScene, this));
    auto awards = cocos2d::MenuItemImage::create("buttons/results.png", "buttons/results.png", CC_CALLBACK_0(PauseScene::goToAwardsWall, this));

    auto menu = cocos2d::Menu::create(resumeItem, retryItem, mainMenuItem, awards, nullptr);

    menu->alignItemsVerticallyWithPadding(cocos2d::Director::getInstance()->getVisibleSize().height / 8);
    this->addChild(menu);
}

void PauseScene::initAudio()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/intro.ogg");
    _pauseSceneAudio = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/intro.ogg");
}
