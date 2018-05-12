//
//  Environment.cpp
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

#include "Environment.h"

void Environment::updateEnemyCount(int newCount){
	enemiesPresent = newCount;
}

int Environment::getEnemyCount() {
	return enemiesPresent;
}

void Environment::resetWorld() {
	enemiesPresent = 0;
	timeSinceWavePast = 0;
	for (
		 orxOBJECT *obj = (orxOBJECT*)orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT);
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))
		 ) {
		orxSTRING name = (orxSTRING)orxObject_GetName(obj);
		if (orxString_Compare(name, "Bullet") == 0 ||
			orxString_Compare(name, "Enemy") == 0) {
			Entity* entity = (Entity*)orxObject_GetUserData(obj);
			entity->despawn();
		}
	}
}

orxVECTOR Environment::randomPosition(orxFLOAT xmin, orxFLOAT xmax, orxFLOAT ymin, orxFLOAT ymax, orxBOOL edge) {
	orxFLOAT x = orxMath_GetRandomFloat(xmin, xmax);
	orxFLOAT y = orxMath_GetRandomFloat(ymin, ymax);
	if (edge) {
		int side = orxMath_GetRandomU32(0, 3);
		switch (side) {
			case 0:
				x = xmin;
				break;
			case 1:
				y = ymin;
				break;
			case 2:
				x = xmax;
				break;
			case 3:
				y = ymax;
				break;
			default:
				x = xmin;
				y = ymin;
				break;
		}
	}
	return {x, y, 0};
}

void Environment::update(orxFLOAT dt) {
	if (enemiesPresent <= 0) {
		timeSinceWavePast += dt;
	}
	if (timeSinceWavePast > waveDelay) {
		timeSinceWavePast = 0;
		enemiesPresent = orxMath_GetRandomU32(1, 10);
		for (int i = 0; i < enemiesPresent; i++) {
			new Enemy(randomPosition(-490.0f, 490.0f, -290.0f, 290.0f, orxTRUE));
		}
	}
	timeSincePowerupSpawn += dt;
	if (timeSincePowerupSpawn > powerupDelay) {
		timeSincePowerupSpawn = 0;
		if (orxMath_GetRandomU32(0, 100) < powerupSpawnProbability) {
			//
		}
	}
	timeSinceItemSpawn += dt;
	if (timeSinceItemSpawn > itemDelay) {
		timeSinceItemSpawn = 0;
		if (orxMath_GetRandomU32(0, 100) < itemSpawnProbability) {
			WeaponType type = (WeaponType)orxMath_GetRandomU32(1, WEAPONCOUNT);
			new Obtainable(randomPosition(-490.0f, 490.0f, -290.0f, 290.0f, orxFALSE), Weapon::copyOf(type));
		}
	}
}
