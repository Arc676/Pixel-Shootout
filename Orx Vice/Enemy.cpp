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

Enemy::Enemy() {
	orxConfig_Load("Entities.ini");
	entity = orxObject_CreateFromConfig("Enemy");
	orxObject_SetUserData(entity, this);
}

void Enemy::update(orxVECTOR playerPos) {
	if (orxVector_GetDistance(&position, &playerPos) < 10) {
		orxVECTOR dir;
		orxVector_Sub(&dir, &playerPos, &position);
		orxVector_Normalize(&dir, &dir);
		orxVector_Mulf(&dir, &dir, 2);
		orxVector_Add(&position, &position, &dir);
		orxObject_SetPosition(entity, &position);
	}
	double rot = Entity::angleBetween(position, playerPos);
	orxObject_SetRotation(entity, rot);
}
