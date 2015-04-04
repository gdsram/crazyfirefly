/*! \brief This file have the implementation for Healt class.
    \file healt.cc
    \author Alvaro Denis <denisacostaq\@gmail.com>
    \date Tue Oct 21 12:17:47 CDT 2014

    \copyright

    \attention <h1><center><strong>COPYRIGHT &copy; 2015 </strong>
    [<strong>Alvaro Denis</strong>][DENISACOSTAQ-URL]. All rights reserved.</center></h1>

    <h3>This file is part of [Saving Las Vegas][SAVINGLASVEGAS-URL] project</h3>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the University nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.

    [DENISACOSTAQ-URL]: https://about.me/denisacostaq/ "Software Developer."
    [SAVINGLASVEGAS-URL]: https://savinglasvegas.com/ "A cocos2d-x based game."
 */

#include "health.h"

bool Health::init()
{
  if (!cocos2d::Sprite::initWithFile(
        "animations/health/healt_background.png")) {
    return false;
  }

  this->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
  this->setPosition(
              cocos2d::Vec2{C_DIRECTOR_->getVisibleSize().width*.15f,
                            C_DIRECTOR_->getVisibleSize().height} +
              C_DIRECTOR_->getVisibleOrigin());
  return true;
}

void Health::initAtTheBeginningOfTheGame()
{
  this->updatePrograsBar();
  this->setVisible(true);
  _healthBackground->setVisible(true);
}

const std::uint8_t Health::health() const
{
  return _health;
}

void Health::setHealth(const std::uint8_t& health)
{
  _health = health;
  if (_health > 100) {
      _health = 100;
  } else if (_health < 0) {
      _health = 0;
  }

  this->stopAllActions();

  if (_health <= 10) {
    this->runAction(cocos2d::RepeatForever::create(cocos2d::Blink::create(1.f, 3)));
  } else if (_health <= 30) {
    this->runAction(cocos2d::RepeatForever::create(cocos2d::Blink::create(1.f, 2)));
  }
  this->updatePrograsBar();
}

void Health::setHealthBackground(cocos2d::Sprite *hb)
{
  _healthBackground = hb;

  float xScale{
    C_DIRECTOR_->getOpenGLView()->getFrameSize().width/
      C_DIRECTOR_->getOpenGLView()->getDesignResolutionSize().width};
  _healthBackground->setScaleX(xScale);
  this->setScaleX(xScale);
}

cocos2d::Sprite* Health::healthBackground() const
{
  return _healthBackground;
}

void Health::setVisible(bool visible)
{
  cocos2d::Sprite::setVisible(visible);
}

void Health::stop()
{
  this->stopAllActions();
}

void Health::updatePrograsBar()
{
  std::uint8_t sufix{0u};
  if (_health < 10) {
    sufix = 0u;
    this->setVisible(false);
    return;
  } else if (_health < 20) {
    sufix = 10u;
  } else if (_health < 30) {
    sufix = 20u;
  } else if (_health < 40) {
    sufix = 30u;
  } else if (_health < 50) {
    sufix = 40u;
  } else if (_health < 60) {
    sufix = 50u;
  } else if (_health < 70) {
    sufix = 60u;
  } else if (_health < 80) {
    sufix = 70u;
  } else if (_health < 90) {
    sufix = 80u;
  } else if (_health < 100) {
    sufix = 90u;
  } else {
      sufix = 100u;
      this->stopAllActions();
  }

  this->setVisible(true);
  char path[200]{0};
  snprintf(path, sizeof(path), "animations/health/healt_value_%u.png", sufix);
  this->setSpriteFrame(cocos2d::Sprite::create(path)->getSpriteFrame());
}
