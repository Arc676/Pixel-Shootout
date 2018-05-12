//
//  StandAlone.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = nullptr;
Player* StandAlone::player = nullptr;
Environment* StandAlone::environment = nullptr;
int StandAlone::paused = 0;

orxOBJECT* StandAlone::deathScreen = nullptr;
orxOBJECT* StandAlone::scoreLabel = nullptr;
orxOBJECT* StandAlone::weaponLabel = nullptr;

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

	orxConfig_Load("Entities.ini");

	player = new Player();
	environment = new Environment();

	orxConfig_Load("UI.ini");
	scoreLabel = orxObject_CreateFromConfig("ScoreLabel");
	weaponLabel = orxObject_CreateFromConfig("WeaponLabel");

	orxConfig_Load("Items.ini");

	orxCLOCK* upClock = orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE);
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
	if (orxInput_IsActive("Pause") && orxInput_HasNewStatus("Pause") && player->getHP() > 0) {
		orxPhysics_EnableSimulation(paused);
		paused = !paused;
	}
	if (paused) {
		if (player->getHP() <= 0 && orxInput_IsActive("Fire")) {
			paused = 0;
			orxPhysics_EnableSimulation(orxTRUE);
			orxObject_SetLifeTime(deathScreen, 0);
			player->respawn();
			environment->resetWorld();
			orxObject_SetTextString(scoreLabel, "Score: 0");
		}
		return;
	}
	if (player->getHP() <= 0) {
		paused = 1;
		orxPhysics_EnableSimulation(orxFALSE);
		deathScreen = orxObject_CreateFromConfig("YouDied");
		return;
	}
	int enemiesStillPresent = 0;
	orxVECTOR mouse = GetMouseWorldPosition();
	orxFLOAT delta = clockInfo->fDT;
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
						   mouse,
						   delta);
		} else if (orxString_Compare(name, "Enemy") == 0) {
			Enemy* e = (Enemy*)orxObject_GetUserData(obj);
			e->update(player->getPosition(), delta);
			if (e->getHP() > 0) {
				enemiesStillPresent++;
			}
		}
	}
	environment->updateEnemyCount(enemiesStillPresent);
	environment->update(delta);
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

void StandAlone::bulletEvent(orxOBJECT* bulletObj, orxOBJECT* otherObj) {
	Bullet* bullet = (Bullet*)orxObject_GetUserData(bulletObj);
	orxSTRING name = (orxSTRING)orxObject_GetName(otherObj);
	if (orxString_Compare(name, "Enemy") == 0 ||
		orxString_Compare(name, "Player") == 0) {
		Character* character = (Character*)orxObject_GetUserData(otherObj);
		character->takeHit(bullet);
		if (orxString_Compare(name, "Enemy") == 0) {
			player->earnPoints(10);
			orxCHAR newtext[15];
			orxString_Print(newtext, "Score: %d", player->getScore());
			orxObject_SetTextString(scoreLabel, newtext);
		}
	} else if (orxString_Compare(name, "Bullet") == 0) {
		orxObject_SetLifeTime(otherObj, 0);
	}
	orxObject_SetLifeTime(bulletObj, 0);
}

void StandAlone::itemEvent(orxOBJECT* itemObj, orxOBJECT* characterObj) {
	// enemies can't obtain items due to the collision mask for item hitboxes
    Obtainable* obtainable = (Obtainable*) orxObject_GetUserData(itemObj);
    Character* character = (Character*) orxObject_GetUserData(characterObj);
    character->obtainItem(obtainable->getItem());
    obtainable->despawn();
    player->earnPoints(20);
	orxCHAR newtext[40];
	orxString_Print(newtext, "Weapon: %s", player->getCurrentWeapon()->getName());
	orxObject_SetTextString(weaponLabel, newtext);
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_INPUT:
			break;
		case orxEVENT_TYPE_PHYSICS:
			switch (currentEvent->eID) {
				case orxPHYSICS_EVENT_CONTACT_ADD:
					orxOBJECT* objs[] = {
						orxOBJECT(currentEvent->hSender),
						orxOBJECT(currentEvent->hRecipient)
					};
					for (int i = 0; i < 2; i++) {
						if (orxString_Compare(orxObject_GetName(objs[i]), "Bullet") == 0) {
							bulletEvent(objs[i], objs[1 - i]);
						} else {
							orxConfig_PushSection(orxObject_GetName(objs[i]));
							if (orxConfig_GetBool("IsObtainable")) {
								itemEvent(objs[i], objs[1 - i]);
							}
							orxConfig_PopSection();
						}
					}
					break;
			}
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}
