/*! \brief This file have global utilitis
    \file AppMacros.h
    \author Alvaro Denis Acosta Quesada <denisacostaq\@gmail.com>
    \date Thu Oct 24 23:18:00 CDT 2013

    \brief This file become from: src/portable/AppMacros.h

    \attention <h1><center>&copy; COPYRIGHT
    GNU GENERAL PUBLIC LICENSE Version 2, June 1991</center></h1>

    \copyright

    <h3>This file is part of <a href="http://www.skypedefense.com"><strong>SkypeDenfense</strong></a> program, a small 2D game.</h3>
    Copyright (C) 2013  Alvaro Denis Acosta Quesada mailto:denisacostaq\@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef CRAZYFIREFLY_APPMACROS_H_
#define CRAZYFIREFLY_APPMACROS_H_

#include <cocos2d.h>

typedef enum {
    kBackground = 1,
    kMiddleground,
    kForeground,
    kAboveAll
} GroundPlace;

#define C_USER_DEFAULT_ cocos2d::UserDefault::getInstance()
#define C_DIRECTOR_ cocos2d::Director::getInstance()
#define C_AUDIO_ CocosDenshion::SimpleAudioEngine::getInstance()
#define C_GLOBAL_COLABORATION_ GlobalColaboration::getInstance()
#define C_VERTICAL_MENU_PADDING cocos2d::Director::getInstance()->getVisibleSize().height / 4

const std::string C_FONT_PATH = "fonts/Marker Felt.ttf";
const int C_FONT_SIZE = 36;

struct Resource {
    cocos2d::Size size;
    std::string directory;
};

struct UserDefaultData {
    const char* maxScore{"maxScore"};
    const int maxScoreDefaultValue{0};

    const char* bgMusicVolume{"bgMusicVolume"};
    const float bgMusicVolumeDefalutValue {0.4f};

    const char* effectsMusicVolume{"effectsMusicVolume"};
    const float effectsMusicVolumeDefalutValue {0.6f};

    const char* audioEnabled{"audioEnabled"};
    const bool audioEnabledDefalutValue{true};

    const char* timesHBarHasBeenCrossed{"timesHBarHasBeenCrossed"};
    const int timesHBarHasBeenCrossedDefaultValue{0};

    const char* maxPlayedTime{"maxPlayedTime"};
    const int maxPlayedTimeDefaultValue{0};

    const char* maxTimeWithoutPickingHarmfulItems{"maxTimeWithoutPickingHarmfulItems"};
    const int maxTimeWithoutPickingHarmfulItemsDefaultValue{0};

    const char* maxSurvivalTime{"maxSurvivalTime"};
    const int maxSurvivalTimeDefaultValue{0};

    const char* maxBonusItems{"maxBonusItems"};
    const int maxBonusItemsDefaultValue{0};
};

static Resource smallVerticalResource  =  { cocos2d::Size(320, 480), "IMG/320x480" };
static Resource mediumVerticalResource  =  { cocos2d::Size(640, 960), "IMG/320x480" };
static Resource highVerticalResource  =  { cocos2d::Size(1080, 1920), "IMG/320x480" };

static cocos2d::Size designResolutionSize {highVerticalResource.size};

const UserDefaultData userDefaultData{};

#endif  // CRAZYFIREFLY_APPMACROS_H_
