#include "scenes/credits.h"

#include "app_macros.h"

cocos2d::Scene* Credits::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = Credits::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool Credits::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // label

    cocos2d::Label* label = cocos2d::Label::createWithTTF("Credits", C_FONT_PATH, C_FONT_SIZE);
    label->setAnchorPoint(cocos2d::Point(0, 0));
    label->setPosition(cocos2d::Point(visibleSize.width * .25f,visibleSize.height * .9f));
    this->addChild(label);

    // creating the menu
    _menu = cocos2d::Menu::create();
    auto mainMenu = cocos2d::MenuItemImage::create("buttons/back.png", "buttons/back.png", CC_CALLBACK_0(Credits::goBack, this));
    _menu->addChild(mainMenu);
    _menu->alignItemsVertically();
    _menu->setPositionY(visibleSize.height * .8f);
    this->addChild(_menu);

    return true;
}

void Credits::goBack()
{
    cocos2d::Director::getInstance()->popScene();
}

