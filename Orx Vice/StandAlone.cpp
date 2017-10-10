//
//  StandAlone.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = nullptr;
Player* StandAlone::player = nullptr;
orxCLOCK* StandAlone::upClock = nullptr;
Environment* StandAlone::environment = nullptr;

StandAlone* StandAlone::Instance() {
	if (m_Instance != nullptr) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

StandAlone::StandAlone() {}

orxSTATUS orxFASTCALL StandAlone::Init() {
	orxViewport_CreateFromConfig("Viewport");
	orxConfig_Load("StaticScene.ini");
	orxObject_CreateFromConfig("Scene");

	player = new Player();
	environment = new Environment(player);

	upClock = orxClock_Create(0.02f, orxCLOCK_TYPE_USER);
	orxClock_Register(upClock, Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);
	orxEvent_AddHandler(orxEVENT_TYPE_INPUT, StandAlone::EventHandler);

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

orxOBJECT* StandAlone::GetObjectByName(orxSTRING objName) {
	for (orxOBJECT* obj = orxOBJECT(orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT));
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))) {
		if (orxString_Compare(orxObject_GetName(obj), objName) == 0) {
			return obj;
		}
	}
	return orxNULL;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	orxVECTOR mouse = GetMouseWorldPosition();
	for (
		 orxOBJECT *obj = (orxOBJECT*)orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT);
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))
		) {
		orxSTRING name = (orxSTRING)orxObject_GetName(obj);
		if (orxString_Compare(name, "Player") == 0) {
			player->update(orxInput_IsActive("GoUp"),
						   orxInput_IsActive("GoDown"),
						   orxInput_IsActive("GoLeft"),
						   orxInput_IsActive("GoRight"),
						   orxInput_IsActive("Fire"),
						   mouse);
		} else if (orxString_Compare(name, "Enemy") == 0) {
			Enemy* e = (Enemy*)orxObject_GetUserData(obj);
			e->update(player->getPosition());
		}
	}
	if (orxInput_IsActive("Spawn")) {
		new Enemy(mouse);
	}
}

orxVECTOR orxFASTCALL StandAlone::GetMouseWorldPosition() {
	orxVECTOR worldpos, screenpos;

	orxRender_GetWorldPosition(orxMouse_GetPosition(&screenpos), orxNULL, &worldpos);
	worldpos.fZ = 0;

	return worldpos;
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_INPUT:
			break;
		case orxEVENT_TYPE_PHYSICS:
			switch (currentEvent->eID) {
				case orxPHYSICS_EVENT_CONTACT_ADD:
					orxOBJECT* sender = orxOBJECT(currentEvent->hSender);
					orxOBJECT* receiver = orxOBJECT(currentEvent->hRecipient);
					orxOBJECT* bulletObj = nullptr;
					Bullet* bullet = nullptr;
					Entity* entity = nullptr;
					if (orxString_Compare(orxObject_GetName(sender), "Bullet") == 0) {
						bulletObj = sender;
						bullet = (Bullet*)orxObject_GetUserData(sender);
						entity = (Entity*)orxObject_GetUserData(receiver);
					} else {
						bulletObj = receiver;
						bullet = (Bullet*)orxObject_GetUserData(receiver);
						entity = (Entity*)orxObject_GetUserData(sender);
					}
					entity->takeHit(bullet);
					orxObject_SetLifeTime(bulletObj, 0);
					break;
			}
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}
