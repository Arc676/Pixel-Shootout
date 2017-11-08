//
//  Weapon.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 06/11/2017.
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

#include "Weapon.h"

Weapon* Weapon::handgun = new Weapon((char*)"Handgun", 0.5, 10, 80);
Weapon* Weapon::fastGun = new Weapon((char*)"Laser Gun", 0.4, 10, 160);

Weapon::Weapon(orxSTRING name, double firingDelay, int dmg, double bulletSpeed) : Item(name, WEAPON), firingDelay(firingDelay), dmg(dmg), bulletSpeed(bulletSpeed) {}

int Weapon::getDmg() {
	return dmg;
}

double Weapon::getBulletSpeed() {
	return bulletSpeed;
}

double Weapon::getFiringDelay() {
	return firingDelay;
}

Weapon* Weapon::copyOf(WeaponType type) {
	switch (type) {
		case HANDGUN:
			return handgun->copy();
		case FASTGUN:
			return fastGun->copy();
		default:
			return nullptr;
	}
}

Weapon* Weapon::copy() {
	return new Weapon(name, firingDelay, dmg, bulletSpeed);
}
