//
//  Character.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 29/10/2017.
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

#include "Character.h"

orxOBJECT* Character::getEntity() {
	return entity;
}

orxVECTOR Character::getPosition() {
	return position;
}

int Character::getHP() {
	return HP;
}

double Character::angleBetween(orxVECTOR v1, orxVECTOR v2) {
	return orxMATH_KF_PI_BY_2 - (orxFLOAT) atan2(
									 v2.fX - v1.fX,
									 v2.fY - v1.fY);
}

void Character::update(orxFLOAT dt) {
	timeSinceLastShot += dt;
}

void Character::fireBullet(double rot) {
	if (timeSinceLastShot < currentWeapon->getFiringDelay()) {
		return;
	}
	timeSinceLastShot = 0;
	orxVECTOR bpos;
	orxObject_GetPosition(entity, &bpos);
	orxVECTOR ds = {32, 12};
	orxVector_2DRotate(&ds, &ds, rot);
	orxVector_Add(&bpos, &bpos, &ds);

	new Bullet(bpos, currentWeapon->getBulletSpeed(), rot, currentWeapon->getDmg());
}

void Character::takeHit(Bullet* bullet) {
	HP -= bullet->getDmg();
	if (HP <= 0) {
		despawn();
	}
}

void Character::despawn() {
    Entity::despawn();
}

void Character::obtainItem(Item *item) {
	switch (item->getItemType()) {
		case WEAPON:
			currentWeapon = (Weapon*)item;
			break;
		case POWERUP:
			Powerup* powerup = (Powerup*)item;
			switch (powerup->getType()) {
				case SPEED:
					speed *= powerup->getEnhancementFactor();
					break;
				default:
					break;
			}
			break;
	}
}

Weapon* Character::getCurrentWeapon() {
	return currentWeapon;
}
