#include "scenes/awards_wall.h"

#include "global_colaboration.h"
#include "scenes/main_menu_scene.h"

cocos2d::Scene* AwardsWall::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = AwardsWall::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool AwardsWall::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initScreen();

    return true;
}

void AwardsWall::initScreen()
{
    // creating the screen label
    cocos2d::Label* label = cocos2d::Label::createWithTTF("Awards Wall", FONT_PATH, FONT_SIZE);
    label->setAnchorPoint(cocos2d::Point(0, 0));
    label->setPosition(cocos2d::Point(_visibleSize.width * .25f,_visibleSize.height * .9f));
    this->addChild(label);

    initMenu();
    initMedalSprites();
    initAwards();
}

void AwardsWall::initMenu()
{
    _menu = cocos2d::Menu::create();
    auto mainMenu = cocos2d::MenuItemImage::create("buttons/back.png", "buttons/back.png", CC_CALLBACK_0(AwardsWall::goToMainMenuScene, this));
    _menu->addChild(mainMenu);
    _menu->alignItemsVertically();
    _menu->setPositionY(_visibleSize.height * .8f);
    this->addChild(_menu);
}

void AwardsWall::goToMainMenuScene()
{
    cocos2d::Director::getInstance()->popScene();
}

void AwardsWall::initMedalSprites()
{
    _goldMedal = cocos2d::Sprite::create("awards/gold_medal.png");
    this->addChild(_goldMedal);
    _silverMedal = cocos2d::Sprite::create("awards/silver_medal.png");
    this->addChild(_silverMedal);
    _bronzeMedal = cocos2d::Sprite::create("awards/bronze_medal.png");
    this->addChild(_bronzeMedal);
}

void AwardsWall::initAwards()
{
    // played time

    int maxBonusItems = C_GLOBAL_COLABORATION_->getMaxBonusItems();

    if (maxBonusItems > 5)
        createAwardRow( _maxBonusItemsText,"Max Bonus: ", _maxBonusItemsValue, maxBonusItems, _goldMedal, cocos2d::Point(_visibleSize.width * .25f,400));
    else if(maxBonusItems > 3)
        createAwardRow( _maxBonusItemsText,"Max Bonus: ", _maxBonusItemsValue, maxBonusItems, _silverMedal, cocos2d::Point(_visibleSize.width * .25f,400));
    else
        createAwardRow( _maxBonusItemsText,"Max Bonus: ", _maxBonusItemsValue, maxBonusItems, _bronzeMedal, cocos2d::Point(_visibleSize.width * .25f,400));

    // survival time

    int maxSurvivalTime = C_GLOBAL_COLABORATION_->getMaxSurvivalTime();

    if (maxSurvivalTime > 60)
        createAwardRow( _maxSurvivalTimeText,"Survival Time: ", _maxSurvivalTimeValue, maxSurvivalTime, _goldMedal, cocos2d::Point(_visibleSize.width * .25f,150));
    else if(maxBonusItems > 40)
        createAwardRow( _maxSurvivalTimeText,"Survival Time: ", _maxSurvivalTimeValue, maxSurvivalTime, _silverMedal, cocos2d::Point(_visibleSize.width * .25f,150));
    else
        createAwardRow( _maxSurvivalTimeText,"Survival Time: ", _maxSurvivalTimeValue, maxSurvivalTime, _bronzeMedal, cocos2d::Point(_visibleSize.width * .25f,150));

    // played time

    int maxPlayedTime = C_GLOBAL_COLABORATION_->getMaxPlayedTime();

    if (maxPlayedTime > 120)
        createAwardRow( _maxPlayedTimeText,"Playing Time: ", _maxPlayedTimeValue, maxPlayedTime, _goldMedal, cocos2d::Point(_visibleSize.width * .25f,50));
    else if(maxBonusItems > 80)
        createAwardRow( _maxPlayedTimeText,"Playing Time: ", _maxPlayedTimeValue, maxPlayedTime, _silverMedal, cocos2d::Point(_visibleSize.width * .25f,50));
    else
        createAwardRow( _maxPlayedTimeText,"Playing Time: ", _maxPlayedTimeValue, maxPlayedTime, _bronzeMedal, cocos2d::Point(_visibleSize.width * .25f,50));


    // time without picking harmful items

    int maxTimeWithoutPickingHarmfulItems = C_GLOBAL_COLABORATION_->getMaxTimeWithoutPickingHarmfulItems();

    if (maxTimeWithoutPickingHarmfulItems > 60)
        createAwardRow( _maxTimeWithoutPickingHarmfulItemsText,"Avoiding Harmful Items: ", _maxTimeWithoutPickingHarmfulItemsValue, maxTimeWithoutPickingHarmfulItems, _goldMedal, cocos2d::Point(_visibleSize.width * .25f,250));
    else if(maxBonusItems > 40)
        createAwardRow( _maxTimeWithoutPickingHarmfulItemsText,"Avoiding Harmful Items: ", _maxTimeWithoutPickingHarmfulItemsValue, maxTimeWithoutPickingHarmfulItems, _silverMedal, cocos2d::Point(_visibleSize.width * .25f,250));
    else
        createAwardRow( _maxTimeWithoutPickingHarmfulItemsText,"Avoiding Harmful Items: ", _maxTimeWithoutPickingHarmfulItemsValue, maxTimeWithoutPickingHarmfulItems, _bronzeMedal, cocos2d::Point(_visibleSize.width * .25f,250));


    // the times that horizontal bar has been crossed

    int timesHBarHasBeenCrossed = C_GLOBAL_COLABORATION_->getTimesHBarHasBeenCrossed();

    if (timesHBarHasBeenCrossed > 10)
        createAwardRow( _timesHBarHasBeenCrossedText,"Level: ", _timesHBarHasBeenCrossedValue, timesHBarHasBeenCrossed, _goldMedal, cocos2d::Point(_visibleSize.width * .25f,350));
    else if(maxBonusItems > 5)
        createAwardRow( _timesHBarHasBeenCrossedText,"Level: ", _timesHBarHasBeenCrossedValue, timesHBarHasBeenCrossed, _silverMedal, cocos2d::Point(_visibleSize.width * .25f,350));
    else
        createAwardRow( _timesHBarHasBeenCrossedText,"Level: ", _timesHBarHasBeenCrossedValue, timesHBarHasBeenCrossed, _bronzeMedal, cocos2d::Point(_visibleSize.width * .25f,350));

}

void AwardsWall::createAwardRow(cocos2d::Label* text, const std::string& msg, cocos2d::Label* number, int value, cocos2d::Sprite* medal, cocos2d::Point position)
{
    text = cocos2d::Label::createWithTTF(msg, FONT_PATH, FONT_SIZE);
    text->setPosition(position);
    this->addChild(text);

    char score_buffer[10]{0};

    snprintf(score_buffer, sizeof(score_buffer), "%u", value);
    number = cocos2d::Label::createWithTTF(score_buffer, FONT_PATH, FONT_SIZE);
    number->setAnchorPoint(cocos2d::Point(0, 0));
    number->setPosition( cocos2d::Point((text->getPositionX() + text->getContentSize().width) * 1.1f, position.y));
    this->addChild(number);

    medal->setPosition(cocos2d::Point((number->getPositionX() + number->getContentSize().width) * 1.1f, position.y));
}

