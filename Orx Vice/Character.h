//
//  Character.hpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 29/10/2017.
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

#ifndef Character_h
#define Character_h

#include "Bullet.h"
#include "Entity.h"

class Character : public Entity {
protected:
	orxVECTOR position;

	int HP = 1;

	int ticksSinceLastShot = 0;
	void fireBullet(double);

	static double angleBetween(orxVECTOR, orxVECTOR);
	void update(); 
public:
	orxOBJECT* getEntity();
	orxVECTOR getPosition();

	int getHP();
	void takeHit(Bullet*);
};

#endif
