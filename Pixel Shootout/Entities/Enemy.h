//
//  Enemy.h
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

#ifndef Enemy_h
#define Enemy_h

#include "../Entities/Character.h"

class Enemy : public Character {
	orxVECTOR targetPoint;
public:
	Enemy(orxVECTOR);
	Enemy(orxVECTOR, WeaponType);
	void update(orxVECTOR, orxFLOAT);
};

#endif
