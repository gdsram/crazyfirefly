#ifndef CRAZYFIREFLY_SCENE_GAMEOVERSCENE_H_
#define CRAZYFIREFLY_SCENE_GAMEOVERSCENE_H_

#include "cocos2d.h"

#include "award_container.h"

class GameOverScene : public cocos2d::Layer
{

public:
    GameOverScene() = default;

    GameOverScene(const GameOverScene&) = delete;
    GameOverScene& operator=(GameOverScene&) = delete;

    GameOverScene(GameOverScene &&) = default;
    GameOverScene& operator=(GameOverScene&&) = default;

    ~GameOverScene() = default;

    static cocos2d::Scene* createScene(int lastScore);

    virtual bool init();  
    inline void setLabelValue(int value) { label_value_ = value; }

    void goToGamePlayScene(Ref *pSender);
    void goToMainMenuScene(Ref *pSender);
    void goToAwardsWall();

    CREATE_FUNC(GameOverScene)

private:
    cocos2d::Label* _backgroundSprite;
    cocos2d::Label* _lastScoreLabel;
    cocos2d::Label* _maxScoreLabel;
    cocos2d::Sprite* _lastScoreTextSprite;
    cocos2d::Sprite* _maxScoreTextSprite;

    void initScreen();
    void initMenu();
    void initLabels();
    void initAudio();

    int label_value_;
};

#endif // CRAZYFIREFLY_SCENE_GAMEOVERSCENE_H_
