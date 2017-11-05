//
//  Environment.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 29/09/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017 Arc676/Alessandro Vinciguerra

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
	ticksSinceWavePast = 0;
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

void Environment::update() {
	if (enemiesPresent <= 0) {
		ticksSinceWavePast++;
	}
	if (ticksSinceWavePast > waveDelay) {
		ticksSinceWavePast = 0;
		enemiesPresent = orxMath_GetRandomU32(1, 10);
		for (int i = 0; i < enemiesPresent; i++) {
			int side = orxMath_GetRandomU32(0, 3);
			int x, y;
			switch (side) {
				case 0:
					x = -490;
					y = orxMath_GetRandomS32(-290, 290);
					break;

				case 1:
					x = orxMath_GetRandomS32(-490, 490);
					y = -290;
					break;

				case 2:
					x = 490;
					y = orxMath_GetRandomS32(-290, 290);
					break;

				case 3:
					x = orxMath_GetRandomS32(-490, 490);
					y = 290;
					break;

				default:
					x = -400;
					y = -200;
					break;
			}
			new Enemy({(orxFLOAT)x,(orxFLOAT)y,0});
		}
	}
}
