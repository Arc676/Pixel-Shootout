//
//  Player.cpp
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

#include "Player.h"

Player::Player() {
	orxConfig_Load("Player.ini");
	orxInput_Load(orxSTRING_EMPTY);
	entity = orxObject_CreateFromConfig("Player");
	orxObject_SetUserData(entity, this);
}

void Player::update(bool up, bool down, bool left, bool right, bool fire, orxVECTOR mouse) {
	orxObject_GetPosition(entity, &position);
	if (up) {
		position.fY -= speed;
	} else if (down) {
		position.fY += speed;
	}
	if (left) {
		position.fX -= speed;
	} else if (right) {
		position.fX += speed;
	}
	orxObject_SetPosition(entity, &position);

	double dx = mouse.fX - position.fX;
	double dy = mouse.fY - position.fY;
	orxFLOAT rot = M_PI_2 - (orxFLOAT) atan2(dx, dy);
	orxObject_SetRotation(entity, rot);

	if (fire) {
		orxVECTOR velocity = {20 * (orxFLOAT)sin(rot), 20 * (orxFLOAT)cos(rot)};
		orxVECTOR bpos;
		orxObject_GetPosition(entity, &bpos);
		bpos.fX += velocity.fX;
		bpos.fY += velocity.fY;

		orxOBJECT* bullet = orxObject_CreateFromConfig("Bullet");
		orxObject_SetPosition(bullet, &bpos);
		orxObject_SetSpeed(bullet, &velocity);
	}
}
