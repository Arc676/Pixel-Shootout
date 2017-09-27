//
//  Entity.cpp
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

#include "Entity.h"

orxOBJECT* Entity::getEntity() {
	return entity;
}

int Entity::getHP() {
	return HP;
}

double Entity::angleBetween(orxVECTOR v1, orxVECTOR v2) {
	return M_PI_2 - (orxFLOAT) atan2(
									 v2.fX - v1.fX,
									 v2.fY - v1.fY);
}

void Entity::update() {
	ticksSinceLastShot++;
}

void Entity::fireBullet(double rot) {
	if (ticksSinceLastShot < 10) {
		return;
	}
	ticksSinceLastShot = 0;
	orxVECTOR bpos;
	orxObject_GetPosition(entity, &bpos);
	orxVECTOR ds = {32, 12};
	orxVector_2DRotate(&ds, &ds, rot);
	orxVector_Add(&bpos, &bpos, &ds);

	new Bullet(bpos, 80, rot, 10);
}

void Entity::takeHit(Bullet* bullet) {
	HP -= bullet->getDmg();
	if (HP <= 0) {
		orxObject_SetLifeTime(entity, 0);
	}
}
