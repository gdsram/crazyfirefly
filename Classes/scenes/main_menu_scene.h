#ifndef CRAZYFIREFLY_SCENE_MAINMENUSCENE_H_
#define CRAZYFIREFLY_SCENE_MAINMENUSCENE_H_

#include "cocos2d.h"

enum {
    kAudioDisabled = 1,
    kAudioEnabled
};

class MainMenuScene : public cocos2d::Layer
{
public:
    MainMenuScene() = default;

    MainMenuScene(const MainMenuScene&) = delete;
    MainMenuScene& operator=(const MainMenuScene&) = delete;

    MainMenuScene(MainMenuScene&&) = default;
    MainMenuScene& operator=(MainMenuScene&&) = default;

    ~MainMenuScene() = default;

    static cocos2d::Scene* createScene();

    virtual bool init();  
    
	// setting up touch events
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);

    CREATE_FUNC(MainMenuScene)

    void goToGamePlayScene(Ref *pSender);
    void goToCreditsScene();
    void goToAwardsWall();
    void goToHowToPlayScene();
    void menuAudioCallback();
	inline unsigned int getMainMenuAudioId() const { return _mainMenuAudioId; }

private:
    void initMenu();
    void initEventListeners();
    void initBackground();
    bool _isTouching;
    float _touchPosition;
    unsigned int _mainMenuAudioId;

    cocos2d::Menu* _menu;
    cocos2d::Menu* _bottomMenu;
    cocos2d::MenuItemImage* _audioMenuItem;

    cocos2d::Label* _playerScore;
    cocos2d::Sprite* _scoreTextSprite;
    cocos2d::Sprite* _background;
};

#endif // CRAZYFIREFLY_SCENE_MAINMENUSCENE_H_
