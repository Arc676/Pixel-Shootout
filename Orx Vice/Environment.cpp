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

void Environment::update() {
	if (enemiesPresent <= 0) {
		enemiesPresent = arc4random_uniform(10);
		for (int i = 0; i < enemiesPresent; i++) {
			new Enemy({
				(orxFLOAT)(50 + arc4random_uniform(50)),
				(orxFLOAT)(50 + arc4random_uniform(50)),
				0});
		}
	}
}
