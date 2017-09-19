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

	orxCLOCK* animClock = orxClock_Create(0.02f, orxCLOCK_TYPE_USER);
	orxOBJECT* soldier = GetObjectByName("SoldierGraphics");
	if (soldier != orxNULL) {
		orxClock_Register(animClock, Update, soldier, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
		orxObject_SetTargetAnim(soldier, "WalkRight");
	}
	orxEvent_AddHandler(orxEVENT_TYPE_ANIM, StandAlone::EventHandler);
	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);

	orxConfig_Load("Interaction.ini");
	orxInput_Load(orxSTRING_EMPTY);
	orxEvent_AddHandler(orxEVENT_TYPE_INPUT, StandAlone::EventHandler);

	orxObject_CreateFromConfig("Walls");
	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

orxOBJECT* StandAlone::GetObjectByName(std::string objName) {
	std::string name;
	for (orxOBJECT* obj = orxOBJECT(orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT));
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))) {
		name = orxObject_GetName(obj);
		if (name.compare(objName) == 0) {
			return obj;
		}
	}
	return orxNULL;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	orxOBJECT* obj = orxOBJECT(context);
	if (obj != orxNULL) {
		std::string name = orxObject_GetName(obj);
		if (name.compare("SoldierGraphics") == 0) {
			orxVECTOR pos;
			orxOBJECT* soldier = GetObjectByName("SoldierGraphics");
			orxObject_GetPosition(soldier, &pos);
			if (orxInput_IsActive("GoUp")) {
				pos.fY--;
			} else if (orxInput_IsActive("GoDown")) {
				pos.fY++;
			}
			if (orxInput_IsActive("GoLeft")) {
				pos.fX--;
			} else if (orxInput_IsActive("GoRight")) {
				pos.fX++;
			}
			orxObject_SetPosition(soldier, &pos);

			orxVECTOR mouse = GetMouseWorldPosition();
			double dx = mouse.fX - pos.fX;
			double dy = mouse.fY - pos.fY;
			orxFLOAT rot = M_PI_2 - (orxFLOAT) atan2(dx, dy);
			orxObject_SetRotation(obj, rot);

			if (orxInput_IsActive("Fire")) {
				orxVECTOR velocity = {20 * (orxFLOAT)sin(rot), 20 * (orxFLOAT)cos(rot)};
				orxVECTOR bpos;
				orxObject_GetPosition(soldier, &bpos);
				bpos.fX += velocity.fX;
				bpos.fY += velocity.fY;

				orxOBJECT* bullet = orxObject_CreateFromConfig("Bullet");
				orxObject_SetPosition(bullet, &bpos);
				orxObject_SetSpeed(bullet, &velocity);
			}
		}
	}
}

orxVECTOR orxFASTCALL StandAlone::GetMouseWorldPosition() {
	orxVECTOR worldpos = {0,0,0};
	orxVECTOR screenpos = {0,0,0};

	orxRender_GetWorldPosition(orxMouse_GetPosition(&screenpos), orxNULL, &worldpos);

	return worldpos;
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_INPUT:
			break;
		case orxEVENT_TYPE_PHYSICS:
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}
