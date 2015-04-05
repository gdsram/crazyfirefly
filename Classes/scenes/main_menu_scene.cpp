#include "scenes/main_menu_scene.h"

#include "audio/include/SimpleAudioEngine.h"

#include "app_macros.h"
#include "global_colaboration.h"
#include "scenes/awards_wall.h"
#include "scenes/credits.h"
#include "scenes/game_layer.h"
#include "scenes/how_to_play.h"

cocos2d::Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto *layer = MainMenuScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    // init audio
    if (C_GLOBAL_COLABORATION_->isAudioEnabled()) {

        //C_AUDIO_->preloadEffect("audio/gotoplayscene.wav");
        C_AUDIO_->playBackgroundMusic("audio/intro.ogg", true);
    }

    initMenu();
    initEventListeners();
    initBackground();

    return true;
}

bool MainMenuScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if(touch) {
		return true;
	}
	return false;
}

void MainMenuScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
	return;
}

void MainMenuScene::goToGamePlayScene(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	auto scene = GameLayer::createScene();
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void MainMenuScene::goToAwardsWall()
{
    auto scene = AwardsWall::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void MainMenuScene::goToHowToPlayScene()
{
    auto scene = HowToPlay::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void MainMenuScene::goToCreditsScene()
{
    auto scene = Credits::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void MainMenuScene::menuAudioCallback() {

    cocos2d::Menu* menu = static_cast<cocos2d::Menu*>(this->getChildByName("mainmenu"));

    if (C_GLOBAL_COLABORATION_->isAudioEnabled()) {

        C_GLOBAL_COLABORATION_->setAudioEnabled(false);
        C_AUDIO_->pauseBackgroundMusic();

        auto frame = cocos2d::Sprite::create("buttons/audio_off.png")->getSpriteFrame();
        _audioMenuItem->setNormalSpriteFrame(frame);

    } else {

        C_GLOBAL_COLABORATION_->setAudioEnabled(true);
        C_AUDIO_->resumeBackgroundMusic();

        auto frame = cocos2d::Sprite::create("buttons/audio_on.png")->getSpriteFrame();
        _audioMenuItem->setNormalSpriteFrame(frame);
    }

    menu->alignItemsVerticallyWithPadding(C_VERTICAL_MENU_PADDING);
}

void MainMenuScene::initMenu()
{
    auto _playItem = cocos2d::MenuItemImage::create("buttons/play.png", "buttons/play.png", CC_CALLBACK_1(MainMenuScene::goToGamePlayScene, this));

    _menu = cocos2d::Menu::create();
    _menu->addChild(_playItem);
    _menu->alignItemsVerticallyWithPadding(C_VERTICAL_MENU_PADDING);
    this->addChild(_menu, 1, "mainmenu");

    // creating the bottom menu
    _bottomMenu = cocos2d::Menu::create();
    auto credits = cocos2d::MenuItemImage::create("buttons/credits.png", "buttons/credits.png", CC_CALLBACK_0(MainMenuScene::goToCreditsScene, this));
    auto results = cocos2d::MenuItemImage::create("buttons/results.png", "buttons/results.png", CC_CALLBACK_0(MainMenuScene::goToAwardsWall, this));
    _audioMenuItem = cocos2d::MenuItemImage::create("buttons/audio_on.png", "buttons/audio_on.png", CC_CALLBACK_0(MainMenuScene::menuAudioCallback, this));
    auto howToPlay = cocos2d::MenuItemImage::create("buttons/howtoplay.png", "buttons/howtoplay.png", CC_CALLBACK_0(MainMenuScene::goToHowToPlayScene, this));

    _bottomMenu->addChild(credits, 1, "credits");
    _bottomMenu->addChild(results, 2, "results");
    _bottomMenu->addChild(_audioMenuItem, 3, "audio");
    _bottomMenu->addChild(howToPlay, 4, "howto");
    _bottomMenu->alignItemsHorizontally();
    _bottomMenu->setPosition(cocos2d::Point(C_DIRECTOR_->getVisibleSize().width * 0.5, C_DIRECTOR_->getVisibleSize().height * 0.1));
    this->addChild(_bottomMenu, 1, "bottommenu");
}

void MainMenuScene::initEventListeners()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainMenuScene::initBackground()
{
    _background = cocos2d::Sprite::create("background.png");
    _background->setPosition(cocos2d::Point(C_DIRECTOR_->getVisibleSize().width * 0.5f, C_DIRECTOR_->getVisibleSize().height * 0.5f));
    addChild(_background, 0);
}
