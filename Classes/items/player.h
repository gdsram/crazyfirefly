#ifndef CRAZYFIREFLY_ITEMS_PLAYER_H_
#define CRAZYFIREFLY_ITEMS_PLAYER_H_

#include "cocos2d.h"

const short int C_INITIAL_PLAYER_ENERGY = 100;
const float C_MIN_SPEED_FACTOR = 0.75f;
const float C_MAX_SPEED_FACTOR = 1.25f;

class Player : public cocos2d::Sprite {
public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;

    ~Player() = default;

    inline short int getEnergy() const { return _energy; }
    inline float getMinScale() const { return _minScale; }
    inline float getMaxScale() const { return _maxScale; }
    inline float getScore() const { return _score; }
    inline cocos2d::Point getNextPosition() { return _next_position; }
    inline float getRadius() const { return getBoundingBox().size.width / 2; }

    inline void setMinScale(float min_scale) { _minScale = min_scale; }
    inline void setMaxScale(float max_scale) { _maxScale = max_scale; }
    inline void setScore(int score) { _score = score; }
    inline void setNextPosition(const cocos2d::Point& next_position) { _next_position = next_position; }

    static Player* create(float minScale, float maxScale, float speed);
    void reset();
    void resetEnergy();
    void resetSize();
    void runScaleAction(float scaleToValue);
    float getSpeed() const;
    void setEnergy(short int energy);

private:
    Player();
    Player(float minScale, float maxScale, float speed);
    void initPlayer();
    void setSpeed(float speed);

    const float C_INITIAL_PLAYER_SPEED = cocos2d::Director::getInstance()->getVisibleSize().height * 0.3f;
    cocos2d::Size _screenSize;
    float _speed;
    short int _energy;
    float _minScale;
    float _maxScale;
    int _score;
    cocos2d::Point _next_position;
};

#endif // CRAZYFIREFLY_ITEMS_PLAYER_H_


