//
//  Environment.h
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 29/09/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017-8 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#ifndef Environment_h
#define Environment_h

#include "orx.h"

#include "../Entities/Player.h"
#include "../Entities/Enemy.h"

#include "../Items/Obtainable.h"
#include "../Items/Powerup.h"

#include "../Combat/Weapon.h"

class Environment {
	orxFLOAT timeSincePowerupSpawn = 0;
	orxFLOAT powerupDelay = 30;
	int powerupSpawnProbability = 60;

	orxFLOAT timeSinceItemSpawn = 0;
	orxFLOAT itemDelay = 30;
	int itemSpawnProbability = 60;

	int enemiesPresent = 0;
	orxFLOAT timeSinceWavePast = 0;
	orxFLOAT waveDelay = 3;
public:
	int getEnemyCount();
	void updateEnemyCount(int);

	void update(orxFLOAT);
	void resetWorld();

	static orxVECTOR randomPosition(orxFLOAT, orxFLOAT, orxFLOAT, orxFLOAT, orxBOOL);
};

#endif
