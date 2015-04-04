#ifndef CRAZYFIREFLY_AWARDCONTAINER_H_
#define CRAZYFIREFLY_AWARDCONTAINER_H_

#include "cocos2d.h"

class AwardContainer : public cocos2d::Sprite {
public:
    AwardContainer() = default;

    AwardContainer(const AwardContainer&) = delete;
    AwardContainer& operator=(AwardContainer&) = delete;

    AwardContainer(AwardContainer &&) = delete;
    AwardContainer& operator=(AwardContainer&&) = delete;

    ~AwardContainer() = default;

    virtual void initContainer();

    static AwardContainer* createAwardContainer(float paddingY = .0f);
    static AwardContainer* createAwardContainer(float x , float y, float paddingY);
    void createAwardAnimation(const std::string& path);

private:
    explicit AwardContainer(float paddingY);
    AwardContainer(float x, float y, float paddingY);

    void addAward(const std::string& path);
    void showWithHorizonalEase();
    cocos2d::Size _visibleSize;

    float _positionX;
    float _positionY;
    float _paddingY;
    cocos2d::Vector<Sprite*> _awardsVector;
};

#endif // CRAZYFIREFLY_AWARDCONTAINER_H_
