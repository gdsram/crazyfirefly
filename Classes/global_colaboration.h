/*! \brief This file have the interface for GlobalColaboration class
    \file Asteroids.h
    \author Alvaro Denis Acosta Quesada <denisacostaq\@gmail.com>
    \date Tue May 27 02:20:00 CDT 2014

    \brief This file become from: src/portable/Asteroids.h

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

#ifndef CRAZYFIREFLY_GLOBALCOLABORATION_H_
#define CRAZYFIREFLY_GLOBALCOLABORATION_H_

#include <cocos2d.h>

#include "app_macros.h"

class GlobalColaboration {
public:
    GlobalColaboration(const GlobalColaboration&) = delete;
    GlobalColaboration& operator=(const GlobalColaboration&) = delete;

    GlobalColaboration(const GlobalColaboration&&) = delete;
    GlobalColaboration& operator=(const GlobalColaboration&&) = delete;

    static GlobalColaboration *getInstance();

    inline const float& getBgMusicVolume() const {
        return _bgMusicVolume;
    }
    inline const float& getEffectsMusicVolume() const {
        return _effectsMusicVolume;
    }

    inline const bool isAudioEnabled() const {
        return _audioEnabled;
    }

    inline const int getMaxScore() const {
        return _maxScore;
    }

    inline const int getTimesHBarHasBeenCrossed() const {
        return _timesHBarHasBeenCrossed;
    }

    inline const int getMaxPlayedTime() const {
        return _maxPlayedTime;
    }

    inline const int getMaxTimeWithoutPickingHarmfulItems() const {
        return _maxTimeWithoutPickingHarmfulItems;
    }

    inline const int getMaxSurvivalTime() const {
        return _maxSurvivalTime;
    }

    inline const int getMaxBonusItems() const {
        return _maxBonusItems;
    }

    inline void incrementTimesHBarHasBeenCrossed(int val) {
        _timesHBarHasBeenCrossed += val;

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.timesHBarHasBeenCrossed, _timesHBarHasBeenCrossed);
            C_USER_DEFAULT_->flush();
    }

    inline void setMaxPlayedTime(int val) {
        _maxPlayedTime += val;

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.maxPlayedTime, _maxPlayedTime);
            C_USER_DEFAULT_->flush();
    }

    inline void setMaxTimeWithoutPickingHarmfulItems(int val) {
        _maxTimeWithoutPickingHarmfulItems = MAX(val, _maxTimeWithoutPickingHarmfulItems);

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.maxTimeWithoutPickingHarmfulItems, _maxTimeWithoutPickingHarmfulItems);
            C_USER_DEFAULT_->flush();
    }

    inline void setMaxSurvivalTime(int val) {
        _maxSurvivalTime = MAX(val, _maxSurvivalTime);

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.maxSurvivalTime, _maxSurvivalTime);
            C_USER_DEFAULT_->flush();
    }

    inline void setBgMusicVolume(const float &val) {
        if (C_USER_DEFAULT_->isXMLFileExist()) {
            C_USER_DEFAULT_->setFloatForKey(
                        userDefaultData.bgMusicVolume, (_bgMusicVolume = val));
            C_USER_DEFAULT_->flush();
        }
    }

    inline void setEffectsMusicVolume(const float &val) {
        if (C_USER_DEFAULT_->isXMLFileExist()) {
            C_USER_DEFAULT_->setFloatForKey(
                        userDefaultData.effectsMusicVolume, (_effectsMusicVolume = val));
            C_USER_DEFAULT_->flush();
        }
    }

    inline void setAudioEnabled(const bool val) {
        _audioEnabled = val;

        if (C_USER_DEFAULT_->isXMLFileExist()) {
            C_USER_DEFAULT_->setBoolForKey(
                        userDefaultData.audioEnabled, val);
            C_USER_DEFAULT_->flush();
        }
    }

    inline void setMaxScore(int val) {
        _maxScore = MAX(val, _maxScore);

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.maxScore, _maxScore);
            C_USER_DEFAULT_->flush();
    }

    inline void setMaxBonusItem(int val) {
        _maxBonusItems = MAX(val, _maxBonusItems);

            C_USER_DEFAULT_->setIntegerForKey(
                        userDefaultData.maxBonusItems, _maxBonusItems);
            C_USER_DEFAULT_->flush();
    }

private:
    static GlobalColaboration* _selfInstance;
    GlobalColaboration();
    ~GlobalColaboration();

    float _bgMusicVolume;
    float _effectsMusicVolume;
    bool _audioEnabled;
    int _maxScore;
    int _currentScore;
    int _timesHBarHasBeenCrossed;
    int _maxPlayedTime;
    int _maxTimeWithoutPickingHarmfulItems;
    int _maxSurvivalTime;
    int _maxBonusItems;

    void loadBgMusicVolume();
    void loadEffectsMusicVolume();
    void loadAudioEnabled();
    void loadMaxScore();
    void loadTimesHBarHasBeenCrossed();
    void loadMaxPlayedTime();
    void loadMaxTimeWithoutPickingHarmfulItems();
    void loadMaxSurvivalTime();
    void loadMaxBonusItems();
};

#endif  // CRAZYFIREFLY_GLOBALCOLABORATION_H_
