#include "horizontal_bar.h"

HorizontalBar::HorizontalBar()
    : _screenSize{ cocos2d::Director::getInstance()->getVisibleSize() }
    , _minGapWidth { C_MIN_GAP_WIDTH }
    , _barHeight{ C_INITIAL_BAR_HEIGHT }
    , _activeSide{ kBottomSide }

{
    _gap = cocos2d::Sprite::create();
    _rightBlock = cocos2d::Sprite::create("hbar2.png");
    _leftBlock = cocos2d::Sprite::create("hbar2.png");
}

bool HorizontalBar::init()
{
    if (!cocos2d::Sprite::init()) {
      return false;
    }

	// init the horizontal bar
    this->setTextureRect(cocos2d::Rect(.00f, .00f, _screenSize.width, _barHeight));
    this->setOpacity(0);
	this->setVisible(false);

	// init the gap
	if (_gap) {
        _gap->setTextureRect(cocos2d::Rect(.00f, .00f, C_MIN_GAP_WIDTH, getBarHeight()));
        _gap->setAnchorPoint(cocos2d::Point(0, 0));
		_gap->setOpacity(0);
		this->addChild(_gap);
	}

    // init the bar blocks
    _leftBlock->setAnchorPoint(cocos2d::Point(0, 0));
    this->addChild(_leftBlock, 2);

    _rightBlock->setAnchorPoint(cocos2d::Point(0, 0));
    this->addChild(_rightBlock, 2);

    return true;
}

bool HorizontalBar::isAtTop() const
{
    float thresholdY =  _screenSize.height - getBarHeight();

    if (isVisible() && getPositionY() > thresholdY)
        return true;
    return false;
}

void HorizontalBar::reset()
{
    setVisible(false);
    setGapWidth(C_MIN_GAP_WIDTH);
}

void HorizontalBar::updateHorizontalBar()
{
    _gap->setPositionX(getRandomPositionXForGap());

    // making sure that an anchor point change will not affect the horizontal bar position
    float x2 = _gap->getPositionX();
    float x3 = x2 + _gap->getContentSize().width;

    _leftBlock->setPositionX(x2 - _leftBlock->getBoundingBox().size.width);
    _rightBlock->setPositionX(x3);
}

float HorizontalBar::getRandomPositionXForGap()
{
    float fromValue = .00f;
    float toValue = _screenSize.width - _gap->getContentSize().width;
	int gapPositionX = fromValue + rand() % (int)toValue;

	return gapPositionX;
}
