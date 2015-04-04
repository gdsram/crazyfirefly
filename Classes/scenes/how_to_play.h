#ifndef CRAZYFIREFLY_SCENE_HOWTOPLAY_H_
#define CRAZYFIREFLY_SCENE_HOWTOPLAY_H_

#include "cocos2d.h"

class HowToPlay : public cocos2d::Layer
{
public:
    HowToPlay() = default;

    HowToPlay(const HowToPlay&) = delete;
    HowToPlay& operator=(HowToPlay&) = delete;

    HowToPlay(HowToPlay &&) = default;
    HowToPlay& operator=(HowToPlay&&) = default;

    ~HowToPlay() = default;

    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(HowToPlay)

private:
    void goToMainMenuScene();

    cocos2d::Sprite* _backButton;

    cocos2d::Label* _maxPlayedTimeText;
    cocos2d::Label* _maxPlayedTimeValue;

    cocos2d::Label* _maxSurvivalTimeText;
    cocos2d::Label* _maxSurvivalTimeValue;

    cocos2d::Label* _maxTimeWithoutPickingHarmfulItemsText;
    cocos2d::Label* _maxTimeWithoutPickingHarmfulItemsValue;

    cocos2d::Label* _timesHBarHasBeenCrossedText;
    cocos2d::Label* _timesHBarHasBeenCrossedValue;

    cocos2d::Menu* _menu;
};

#endif // CRAZYFIREFLY_SCENE_HOWTOPLAY_H_
