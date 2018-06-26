//
//  Player.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 25/09/2017.
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

#include "Player.h"

Player::Player() {
	orxInput_Load(orxSTRING_EMPTY);
	entity = orxObject_CreateFromConfig("Player");
	orxObject_SetUserData(entity, this);
	currentWeapon = Weapon::copyOf(HANDGUN);
}

void Player::respawn() {
	orxVECTOR pos = {0, 0, 0};
	orxObject_SetPosition(entity, &pos);
	HP = 1;
    currentWeapon = Weapon::copyOf(HANDGUN);
	timeSinceLastShot = 0;
	score = 0;
}

void Player::despawn() {}

int Player::getScore() {
	return score;
}

void Player::earnPoints(int amt) {
	score += amt;
}

void Player::update(bool up, bool down, bool left, bool right, bool fire, orxVECTOR mouse, orxFLOAT dt) {
	if (HP <= 0) {
		return;
	}
	Character::update(dt);
	orxObject_GetPosition(entity, &position);
	if (up) {
		position.fY -= speed * dt;
	} else if (down) {
		position.fY += speed * dt;
	}
	if (left) {
		position.fX -= speed * dt;
	} else if (right) {
		position.fX += speed * dt;
	}
	orxObject_SetPosition(entity, &position);

	double rot = Character::angleBetween(position, mouse);
	orxObject_SetRotation(entity, rot);

	if (fire) {
		fireBullet(rot);
	}
}
