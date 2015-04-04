#ifndef CRAZYFIREFLY_SCENE_AWARDSSCENE_H_
#define CRAZYFIREFLY_SCENE_AWARDSSCENE_H_

#include "cocos2d.h"

const std::string FONT_PATH = "fonts/Marker Felt.ttf";
const int FONT_SIZE = 24;

class AwardsWall : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(AwardsWall)

private:
    void goToMainMenuScene();
    void initScreen();
    void initMenu();
    void initMedalSprites();
    void initAwards();
    void createAwardRow(cocos2d::Label* text, const std::string& msg, cocos2d::Label* number, int value, cocos2d::Sprite* medal, cocos2d::Point position);

    cocos2d::Sprite* _backButton;

    cocos2d::Label* _maxPlayedTimeText;
    cocos2d::Label* _maxPlayedTimeValue;

    cocos2d::Label* _maxSurvivalTimeText;
    cocos2d::Label* _maxSurvivalTimeValue;

    cocos2d::Label* _maxTimeWithoutPickingHarmfulItemsText;
    cocos2d::Label* _maxTimeWithoutPickingHarmfulItemsValue;

    cocos2d::Label* _timesHBarHasBeenCrossedText;
    cocos2d::Label* _timesHBarHasBeenCrossedValue;

    cocos2d::Label* _maxBonusItemsText;
    cocos2d::Label* _maxBonusItemsValue;

    cocos2d::Menu* _menu;

    cocos2d::Sprite* _goldMedal;
    cocos2d::Sprite* _silverMedal;
    cocos2d::Sprite* _bronzeMedal;

    cocos2d::Size _visibleSize;
};

#endif // CRAZYFIREFLY_SCENE_AWARDSSCENE_H_
