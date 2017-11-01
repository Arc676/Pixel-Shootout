//
//  Enemy.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 25/09/2017.
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

#include "Enemy.h"

Enemy::Enemy(orxVECTOR pos) {
	entity = orxObject_CreateFromConfig("Enemy");
	position = pos;
	targetPoint = pos;
	orxObject_SetPosition(entity, &position);
	orxObject_SetUserData(entity, this);
}

void Enemy::update(orxVECTOR playerPos, orxFLOAT dt) {
	Character::update();
	orxObject_GetPosition(entity, &position);
	orxOBJECT* collide = orxObject_Raycast(&position, &playerPos, 0xFFFF, 0xFFFB, orxFALSE, nullptr, nullptr);
	orxSTRING name = (orxSTRING)orxObject_GetName(collide);
	if (collide != orxNULL &&
		(orxString_Compare(name, "Player") == 0 || orxString_Compare(name, "Enemy") == 0)) {
		if (orxVector_GetDistance(&position, &playerPos) > 200) {
			orxVECTOR dir;
			orxVector_Sub(&dir, &playerPos, &position);
			orxVector_Normalize(&dir, &dir);
			dir.fZ = 0;
			orxVector_Mulf(&dir, &dir, 50 * dt);
			orxVector_Add(&position, &position, &dir);
			orxObject_SetPosition(entity, &position);
		}
		double rot = Character::angleBetween(position, playerPos);
		orxObject_SetRotation(entity, rot);
		if (orxString_Compare(name, "Player") == 0) {
			fireBullet(rot);
		}
	} else {
		orxVECTOR diff;
		orxVector_Sub(&diff, &targetPoint, &position);
		if (orxVector_GetSize(&diff) <= 40) {
			if (position.fX < -500 || position.fX > 500 || position.fY < -300 || position.fY > 300) {
				orxVector_Neg(&targetPoint, &position);
				orxObject_Raycast(&position, &targetPoint, 0x0002, 0x0008, orxFALSE, &targetPoint, nullptr);
				orxVector_Divf(&targetPoint, &targetPoint, 1.75);
			} else {
				orxVECTOR dir = {
					(orxFLOAT) arc4random_uniform(200) - 100,
					(orxFLOAT) arc4random_uniform(200) - 100,
					0
				};
				orxVector_Add(&targetPoint, &position, &dir);
				orxVector_Copy(&dir, &position);
				orxObject_Raycast(&position, &targetPoint, 0x0002, 0x0008, orxFALSE, &dir, nullptr);
				if (!orxVector_AreEqual(&position, &dir) &&
					orxVector_GetDistance(&position, &dir) < orxVector_GetDistance(&position, &targetPoint)) {
					orxVector_Copy(&targetPoint, &dir);
				}
			}
		} else {
			orxVECTOR dir;
			orxVector_Sub(&dir, &targetPoint, &position);
			orxVector_Normalize(&dir, &dir);
			orxVector_Mulf(&dir, &dir, 50 * dt);
			orxVector_Add(&position, &position, &dir);
			orxObject_SetPosition(entity, &position);

			double rot = Character::angleBetween(position, targetPoint);
			orxObject_SetRotation(entity, rot);
		}
	}
}
