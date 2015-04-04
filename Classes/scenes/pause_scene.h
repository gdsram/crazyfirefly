#ifndef CRAZYFIREFLY_SCENE__PAUSESCENE_H_
#define CRAZYFIREFLY_SCENE__PAUSESCENE_H_

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
    PauseScene() = default;

    PauseScene(const PauseScene&) = delete;
    PauseScene& operator=(const PauseScene&) = delete;

    PauseScene(PauseScene&&) = default;
    PauseScene& operator=(PauseScene&&) = default;

    ~PauseScene() = default;

    static cocos2d::Scene* createScene();
    virtual bool init();  

    void resume(Ref *pSender);
    void goToMainMenuScene(Ref *pSender);
    void retry(Ref *pSender);
    void goToAwardsWall();

	inline unsigned int getPauseSceneAudio() const { return _pauseSceneAudio; }

    CREATE_FUNC(PauseScene)

private:
    void initMenu();
    void initAudio();

    unsigned int _pauseSceneAudio;
};

#endif // CRAZYFIREFLY_SCENE__PAUSESCENE_H_
