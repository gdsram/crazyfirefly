#include "scenes/game_over_scene.h"

#include "../cocos2d/external/flatbuffers/util.h"
#include "SimpleAudioEngine.h"

#include "global_colaboration.h"
#include "scenes/awards_wall.h"
#include "scenes/game_layer.h"
#include "scenes/main_menu_scene.h"

cocos2d::Scene* GameOverScene::createScene(int lastScore)
{
    auto scene = cocos2d::Scene::create();
    auto layer = GameOverScene::create();
    layer->setLabelValue(lastScore);

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    initScreen();
    initAudio();

    return true;
}

void GameOverScene::goToGamePlayScene(cocos2d::Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto scene = GameLayer::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *pSender)
{
    auto scene = MainMenuScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

void GameOverScene::goToAwardsWall()
{
    auto scene = AwardsWall::createScene();
    cocos2d::Director::getInstance()->pushScene(scene);
}

void GameOverScene::initScreen()
{
    // init the background
    cocos2d::Sprite* sprite = cocos2d::Sprite::create("game_over.png");
    sprite->setPosition(cocos2d::Point(C_DIRECTOR_->getVisibleSize().width / 2, C_DIRECTOR_->getVisibleSize().height / 2));
    this->addChild(sprite, kBackground);

    initMenu();
    initLabels();
}

void GameOverScene::initMenu()
{
    auto retryItem = cocos2d::MenuItemImage::create("buttons/try again.png", "buttons/try again.png", CC_CALLBACK_1(GameOverScene::goToGamePlayScene, this));
    auto mainMenuItem = cocos2d::MenuItemImage::create("buttons/main.png", "buttons/main.png", CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));
    auto awards = cocos2d::MenuItemImage::create("buttons/results.png", "buttons/results.png", CC_CALLBACK_0(GameOverScene::goToAwardsWall, this));
    auto menu = cocos2d::Menu::create(retryItem, mainMenuItem, awards, nullptr);

    menu->alignItemsVerticallyWithPadding(C_VERTICAL_MENU_PADDING);
    this->addChild(menu);
}

void GameOverScene::initLabels()
{
    _lastScoreTextSprite = cocos2d::Sprite::createWithSpriteFrameName("label_score.png");
    _lastScoreTextSprite->setAnchorPoint(cocos2d::Point(0,0));
    _lastScoreTextSprite->setPosition(cocos2d::Point(C_DIRECTOR_->getVisibleSize().width * 0.5f - _lastScoreTextSprite->getContentSize().width, C_DIRECTOR_->getVisibleSize().height * 0.5f));
    this->addChild(_lastScoreTextSprite, kForeground);

    _maxScoreTextSprite = cocos2d::Sprite::createWithSpriteFrameName("label_score.png");
    _maxScoreTextSprite->setAnchorPoint(cocos2d::Point(0,0));
    _maxScoreTextSprite->setPosition(cocos2d::Point(C_DIRECTOR_->getVisibleSize().width * 0.5f - _maxScoreTextSprite->getContentSize().width, C_DIRECTOR_->getVisibleSize().height * 0.4f));
    this->addChild(_maxScoreTextSprite, kForeground);

    _lastScoreLabel = cocos2d::Label::createWithBMFont("font.fnt", flatbuffers::NumToString(label_value_), cocos2d::TextHAlignment::LEFT);
    _lastScoreLabel->setAnchorPoint(cocos2d::Point(0, 0));
    _lastScoreLabel->setPosition( cocos2d::Point((_lastScoreTextSprite->getPositionX() + _lastScoreTextSprite->getContentSize().width) * 1.1f, C_DIRECTOR_->getVisibleSize().height * 0.5f * 0.96f));
    this->addChild(_lastScoreLabel, kForeground);

    _maxScoreLabel = cocos2d::Label::createWithBMFont("font.fnt", flatbuffers::NumToString(C_GLOBAL_COLABORATION_->getMaxScore()), cocos2d::TextHAlignment::LEFT);
    _maxScoreLabel->setAnchorPoint(cocos2d::Point(0, 0));
    _maxScoreLabel->setPosition( cocos2d::Point((_maxScoreTextSprite->getPositionX() + _maxScoreTextSprite->getContentSize().width) * 1.1f, C_DIRECTOR_->getVisibleSize().height * 0.4f * 0.96f));
    this->addChild(_maxScoreLabel, kForeground);
}

void GameOverScene::initAudio()
{
    if (C_GLOBAL_COLABORATION_->isAudioEnabled()) {
        C_AUDIO_->playEffect("audio/gameover.ogg");

        if (C_AUDIO_->isBackgroundMusicPlaying()) {
            C_AUDIO_->playBackgroundMusic("audio/intro.ogg", true);
        }
    }
}


