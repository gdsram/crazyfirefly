#include "scenes/how_to_play.h"

#include "app_macros.h"
#include "global_colaboration.h"
#include "scenes/main_menu_scene.h"

cocos2d::Scene* HowToPlay::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = HowToPlay::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HowToPlay::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // label

    cocos2d::Label* label = cocos2d::Label::createWithTTF("How to Play", C_FONT_PATH, C_FONT_SIZE);
    label->setAnchorPoint(cocos2d::Point(0, 0));
    label->setPosition(cocos2d::Point(visibleSize.width * .25f,visibleSize.height * .9f));
    this->addChild(label);

    // creating the menu
    _menu = cocos2d::Menu::create();
    auto mainMenu = cocos2d::MenuItemImage::create("buttons/back.png", "buttons/back.png", CC_CALLBACK_0(HowToPlay::goToMainMenuScene, this));
    _menu->addChild(mainMenu);
    _menu->alignItemsVertically();
    _menu->setPositionY(visibleSize.height * .8f);
    this->addChild(_menu);

    return true;
}

void HowToPlay::goToMainMenuScene()
{
    cocos2d::Director::getInstance()->popScene();
}

