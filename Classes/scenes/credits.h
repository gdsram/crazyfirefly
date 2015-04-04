#ifndef CRAZYFIREFLY_SCENE_SPLASHSCENE_H_
#define CRAZYFIREFLY_SCENE_SPLASHSCENE_H_

#include "cocos2d.h"

class Credits : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    
    CREATE_FUNC(Credits)
private:
    void goBack();
    cocos2d::Menu* _menu;
};

#endif // CRAZYFIREFLY_SCENE_SPLASHSCENE_H_
