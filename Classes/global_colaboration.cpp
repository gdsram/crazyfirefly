/*! \brief This file have the implementatio for GlobalColaboration class
    \file GlobalColaboration.cpp
    \author Alvaro Denis Acosta Quesada <denisacostaq\@gmail.com>
    \date Tue May 27 02:20:00 CDT 2014

    \brief This file become from: src/portable/GlobalColaboration.cpp

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

#include "global_colaboration.h"

GlobalColaboration* GlobalColaboration::_selfInstance {nullptr};

/*!
 * \brief GlobalColaboration::GlobalColaboration hacerle un destructor que
 * \brief funcione a la salida del programa.
 */
GlobalColaboration::GlobalColaboration()
    : _bgMusicVolume { userDefaultData.bgMusicVolumeDefalutValue }
    , _effectsMusicVolume { userDefaultData.effectsMusicVolumeDefalutValue }
    , _audioEnabled { userDefaultData.audioEnabledDefalutValue }
    , _maxScore { 0 }
    , _timesHBarHasBeenCrossed { 0 }
    , _maxPlayedTime { 0 }
    , _maxTimeWithoutPickingHarmfulItems { 0 }
    , _maxSurvivalTime { 0 }
    , _maxBonusItems { 0 }
{
    srand(time(nullptr));
    setAudioEnabled(_audioEnabled);

    // loading configuration from xml file
    loadBgMusicVolume();
    loadEffectsMusicVolume();
    loadAudioEnabled();
    loadMaxScore();
    loadMaxPlayedTime();
    loadTimesHBarHasBeenCrossed();
    loadMaxSurvivalTime();
    loadMaxPlayedTime();
}

GlobalColaboration *C_GLOBAL_COLABORATION_ {
  if (!_selfInstance) {
    _selfInstance = new GlobalColaboration();
  }
  return _selfInstance;
}

/*!
 * \brief GlobalColaboration::~GlobalColaboration es privado, nunca elimine la
 * \brief instancia en una clase que la haya obtenido a traves de getInstance()
 * \sa getInstance ();
 */
GlobalColaboration::~GlobalColaboration() {
}

void GlobalColaboration::loadBgMusicVolume() {
  if (C_USER_DEFAULT_->isXMLFileExist()) {
    _bgMusicVolume =  C_USER_DEFAULT_->getFloatForKey(
                userDefaultData.bgMusicVolume,
                userDefaultData.bgMusicVolumeDefalutValue);
  } else {
    _bgMusicVolume = userDefaultData.bgMusicVolumeDefalutValue;
  }
}

void GlobalColaboration::loadEffectsMusicVolume() {
  if (C_USER_DEFAULT_->isXMLFileExist()) {
    _effectsMusicVolume = C_USER_DEFAULT_->getFloatForKey(
                userDefaultData.effectsMusicVolume,
                userDefaultData.effectsMusicVolumeDefalutValue);
  } else {
    _effectsMusicVolume = userDefaultData.effectsMusicVolumeDefalutValue;
  }
}

void GlobalColaboration::loadAudioEnabled() {
    if (C_USER_DEFAULT_->isXMLFileExist()) {
      _audioEnabled = C_USER_DEFAULT_->getBoolForKey(
                  userDefaultData.audioEnabled,
                  userDefaultData.audioEnabledDefalutValue);
    } else {
      _audioEnabled = userDefaultData.audioEnabledDefalutValue;
    }
}

void GlobalColaboration::loadMaxScore() {
      _maxScore = C_USER_DEFAULT_->getIntegerForKey(
                  userDefaultData.maxScore,
                  userDefaultData.maxScoreDefaultValue);
}

void GlobalColaboration::loadTimesHBarHasBeenCrossed() {
    _timesHBarHasBeenCrossed = C_USER_DEFAULT_->getIntegerForKey(
                userDefaultData.timesHBarHasBeenCrossed,
                userDefaultData.timesHBarHasBeenCrossedDefaultValue);
}

void GlobalColaboration::loadMaxPlayedTime() {
    _maxPlayedTime = C_USER_DEFAULT_->getIntegerForKey(
                userDefaultData.maxPlayedTime,
                userDefaultData.maxPlayedTimeDefaultValue);
}

void GlobalColaboration::loadMaxTimeWithoutPickingHarmfulItems() {
    _maxTimeWithoutPickingHarmfulItems = C_USER_DEFAULT_->getIntegerForKey(
                userDefaultData.maxTimeWithoutPickingHarmfulItems,
                userDefaultData.maxTimeWithoutPickingHarmfulItemsDefaultValue);
}

void GlobalColaboration::loadMaxSurvivalTime() {
    _maxSurvivalTime = C_USER_DEFAULT_->getIntegerForKey(
                userDefaultData.maxSurvivalTime,
                userDefaultData.maxSurvivalTimeDefaultValue);
}

void GlobalColaboration::loadMaxBonusItems() {
    _maxBonusItems = C_USER_DEFAULT_->getIntegerForKey(
                userDefaultData.maxBonusItems,
                userDefaultData.maxBonusItemsDefaultValue);
}
