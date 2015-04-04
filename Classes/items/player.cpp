#include "player.h"

Player::Player()
    : _screenSize(cocos2d::Director::getInstance()->getWinSize())
    , _speed{.00f}
    , _energy{ C_INITIAL_PLAYER_ENERGY }
    , _minScale{ 1.0f }
    , _maxScale{ 1.5f }
    , _score{0}
    , _next_position{ cocos2d::Point::ZERO }
{
}

Player::Player(float minScale, float maxScale, float speed)
    : _screenSize(cocos2d::Director::getInstance()->getWinSize())
    , _speed{ speed }
    , _energy{ C_INITIAL_PLAYER_ENERGY }
    , _minScale{ minScale }
    , _maxScale{ maxScale }
    , _score{ 0 }
    , _next_position{ cocos2d::Point::ZERO }
{
}

Player* Player::create(float minScale, float maxScale, float speed)
{
    Player* _player = new Player(minScale, maxScale, speed);

    if (_player && _player->initWithFile("ball_normal.png")) {
		_player->autorelease();
		_player->initPlayer();

		return _player;
	}

	CC_SAFE_DELETE(_player);
	return nullptr;
}

void Player::reset () 
{
	_energy = C_INITIAL_PLAYER_ENERGY;
    _score = 0;
    this->setScale(1.0f);
    this->setPosition(cocos2d::Point( _screenSize.width * 0.5f, _screenSize.height * 0.5f ));
}

void Player::resetEnergy()
{
    _energy = C_INITIAL_PLAYER_ENERGY;
}

void Player::resetSize()
{
    runAction(cocos2d::ScaleTo::create(0.5f, 1.0f));
}

void Player::runScaleAction(float scaleToValue)
{
    float newScaleValue = MIN(MAX(_minScale, getScale() * scaleToValue), _maxScale);
    runAction(cocos2d::ScaleTo::create(0.5f, newScaleValue));

    // updating player image
    if (newScaleValue > 1.0f) {
        setSpriteFrame(cocos2d::Sprite::create("ball_medium.png")->getSpriteFrame());
    } else if (newScaleValue > 1.75) {
        setSpriteFrame(cocos2d::Sprite::create("ball_hot.png")->getSpriteFrame());
    } else {
        setSpriteFrame(cocos2d::Sprite::create("ball_normal.png")->getSpriteFrame());
    }

    // size alters player's speed
    _speed = getScale() * C_INITIAL_PLAYER_SPEED;
}

float Player::getSpeed() const
{
	return _speed;
}

void Player::setSpeed(float speed)
{
    _speed = speed;
}

void Player::initPlayer ()
{
    this->setPosition(cocos2d::Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->setNextPosition(getPosition());
    this->setColor(cocos2d::Color3B(255,255,255));
}

void Player::setEnergy(short int energy)
{
    _energy = MIN(energy, C_INITIAL_PLAYER_ENERGY);
}
