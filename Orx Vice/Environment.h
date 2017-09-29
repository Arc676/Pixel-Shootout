//
//  Environment.hpp
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

#ifndef Environment_h
#define Environment_h

#include "orx.h"
#include "Player.h"
#include "Enemy.h"

class Environment {
	Player* player;

	static Environment* instance;
public:
	Environment(Player*);
	void registerEntity(Entity* entity);
	orxCLOCK* upClock;

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);
};

#endif
