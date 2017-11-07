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
	currentWeapon = new Weapon((char*)"Handgun", 0.5, 10, 80);
}

Enemy::Enemy(orxVECTOR pos, Weapon* weapon) : Enemy(pos) {
	currentWeapon = weapon;
}

void Enemy::update(orxVECTOR playerPos, orxFLOAT dt) {
	Character::update(dt);
	orxObject_GetPosition(entity, &position);

	orxOBJECT* collide = orxObject_Raycast(&position, &playerPos, 0xFFFF, 0xFFF9, orxTRUE, nullptr, nullptr);
	orxSTRING name = (collide ? (orxSTRING)orxObject_GetName(collide) : (orxSTRING)"");
	double rot;
	orxVECTOR target;
	orxVector_Copy(&target, &position);

	if (collide != orxNULL && orxString_Compare(name, "Player") == 0) {
		if (orxVector_GetDistance(&position, &playerPos) > 200) {
			orxVector_Sub(&target, &playerPos, &position);
		}
		rot = angleBetween(position, playerPos);
		orxOBJECT* otherEnemy = orxObject_Raycast(&position, &playerPos, 0xFFFF, 0x0002, orxTRUE, nullptr, nullptr);
		if (!otherEnemy && orxString_Compare(name, "Player") == 0) {
			fireBullet(rot);
		}
	} else {
		orxVECTOR diff;
		orxVector_Sub(&diff, &targetPoint, &position);
		if (orxVector_GetSize(&diff) <= 40) {
			if (position.fX < -500 || position.fX > 500 || position.fY < -300 || position.fY > 300) {
				targetPoint = {0, 0, 0};
				orxObject_Raycast(&position, &targetPoint, 0x0002, 0x0008, orxFALSE, &targetPoint, nullptr);
				orxVector_Divf(&targetPoint, &targetPoint, 1.75);
			} else {
				orxVECTOR dir = {
					orxMath_GetRandomFloat(-100.0f, 100.0f),
					orxMath_GetRandomFloat(-100.0f, 100.0f),
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
			orxVector_Sub(&target, &targetPoint, &position);
		}
		rot = Character::angleBetween(position, targetPoint);
	}

	if (!orxVector_AreEqual(&position, &target)) {
		orxVector_Normalize(&target, &target);
		target.fZ = 0;
		orxVector_Mulf(&target, &target, 50 * dt);
		orxVector_Add(&position, &position, &target);
		orxObject_SetPosition(entity, &position);
	}
	orxObject_SetRotation(entity, rot);
}
