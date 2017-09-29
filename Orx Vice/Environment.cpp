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

Environment* Environment::instance = nullptr;

Environment::Environment(Player* player) {
	this->player = player;
	upClock = orxClock_Create(0.02f, orxCLOCK_TYPE_USER);
	Environment::instance = this;
}

void Environment::registerEntity(Entity* entity) {
	orxClock_Register(upClock, Update, entity, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
}

void orxFASTCALL Environment::Update(const orxCLOCK_INFO* info, void* context) {
	orxOBJECT* obj = orxOBJECT(context);
	if (obj != orxNULL) {
		orxLOG("found non-null entity to update");
		if (orxString_Compare(orxObject_GetName(obj), "Enemy") == 0) {
			orxLOG("found enemy to update");
			Enemy* e = (Enemy*)orxObject_GetUserData(obj);
			e->update(instance->player->getPosition());
		}
	}
}
