#ifndef CRAZYFIREFLY_ITEMS_HORIZONTALBAR_H_
#define CRAZYFIREFLY_ITEMS_HORIZONTALBAR_H_

#include "cocos2d.h"

enum ActiveSide {
    kBottomSide,
    kTopSide,
    kGapSides
};

class HorizontalBar : public cocos2d::Sprite
{
public:
    CC_SYNTHESIZE(ActiveSide, _activeSide, ActiveSide)

    HorizontalBar();

    HorizontalBar(const HorizontalBar&) = default;
    HorizontalBar& operator=(const HorizontalBar&) = default;

    HorizontalBar(HorizontalBar&&) = default;
    HorizontalBar& operator=(HorizontalBar&&) = default;

    ~HorizontalBar() = default;

    CREATE_FUNC(HorizontalBar)
    virtual bool init() override;

    inline const cocos2d::Sprite* getGap() const {
        return _gap;
    }

    inline const float getMinGapWidth() const {
        return C_MIN_GAP_WIDTH;
    }

    inline void setGapWidth(float width) {
        _gap->setScaleX(width/_gap->getContentSize().width);
    }

    inline float getBarWidth() const {
        return this->getBoundingBox().size.width;
    }

    inline float getBarHeight() const {
        return this->getBoundingBox().size.height;
    }

    inline virtual int left() const {
        return this->getPositionX() - this->getBoundingBox().size.width * getAnchorPoint().x;
    }

    inline virtual int right() const {
        return this->getPositionX() + this->getBoundingBox().size.width * (1 - getAnchorPoint().x);
    }

    inline virtual int top() const {
        return this->getPositionY() + this->getBoundingBox().size.height * (1 - getAnchorPoint().y);
    }

    inline virtual int bottom() const {
        return this->getPositionY() - this->getBoundingBox().size.height * getAnchorPoint().y;
    }

    bool isAtTop() const; // return true if the bar is at the top of the screen
    void reset();
    void updateHorizontalBar();

private:
    float getRandomPositionXForGap();

    cocos2d::Size _screenSize;

    // constants of horizontal bar
    const float C_INITIAL_GAP_WIDTH = _screenSize.width * 0.30f;
    const float C_MIN_GAP_WIDTH = _screenSize.width * 0.15f;
    const float C_INITIAL_BAR_HEIGHT = _screenSize.height * 0.08f;

    float _minGapWidth;
    float _barHeight;

    cocos2d::Sprite *_gap;
    cocos2d::Sprite *_leftBlock; // block at left side of the gap
    cocos2d::Sprite *_rightBlock; // block at right side of the gap
};

#endif // CRAZYFIREFLY_ITEMS_HORIZONTALBAR_H_
