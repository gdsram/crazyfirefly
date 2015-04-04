/*! \brief This file have the interface for Healt class.
    \file healt.h
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

#ifndef CRAZYFIREFLY_ITEMS_HEALTH_H_
#define CRAZYFIREFLY_ITEMS_HEALTH_H_

#include "cocos2d.h"

#include "app_macros.h"

class Health : public cocos2d::Sprite {
public:
    Health() = default;

    Health(const Health&) = delete;
    Health& operator=(const Health&) = delete;

    Health(const Health&&) = delete;
    Health& operator=(const Health&&) = delete;

    ~Health() = default;

    CREATE_FUNC(Health)
    virtual bool init() override;
    void initAtTheBeginningOfTheGame();

    const std::uint8_t health() const;
    void setHealth(const std::uint8_t& healt);
    void setHealthBackground(cocos2d::Sprite *hb);
    cocos2d::Sprite *healthBackground() const;
    virtual void setVisible(bool visible) override;
    void stop();

private:
    void updatePrograsBar();

    std::uint8_t _health;
    cocos2d::Sprite *_healthBackground;
};

#endif // CRAZYFIREFLY_ITEMS_HEALTH_H_
