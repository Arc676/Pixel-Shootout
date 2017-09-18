//
//  StandAlone.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

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

	orxCLOCK* animClock = orxClock_Create(0.2f, orxCLOCK_TYPE_USER);
	orxOBJECT* soldier = GetObjectByName("SoldierGraphics");
	if (soldier != orxNULL) {
		orxClock_Register(animClock, Update, soldier, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
		orxObject_SetTargetAnim(soldier, "WalkRight");
	}
	orxEvent_AddHandler(orxEVENT_TYPE_ANIM, StandAlone::EventHandler);

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
			if (orxInput_IsActive("GoRight")) {
				orxObject_SetTargetAnim(obj, "WalkRight");
			} else if (orxInput_IsActive("GoLeft")) {
				orxObject_SetTargetAnim(obj, "WalkLeft");
			} else {
				orxObject_SetTargetAnim(obj, orxNULL);
			}
		}
	}
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	// We could just use a direct cast, but in case we expand this function later to deal
	//   with different event types, we're going to be careful and make sure we're in the
	//   correct event type first.
	switch( currentEvent->eType ) {
			// This is for animation events, the only ones we handle in tutorial 3.
		case orxEVENT_TYPE_ANIM:
			// Okay so we know we're dealing with an animation, lets grab the 'payload' out of the event.
//			orxANIM_EVENT_PAYLOAD* EventPayload = (orxANIM_EVENT_PAYLOAD*)currentEvent->pstPayload;

			// We want the name of the object who called this event.
			//   (In tutorial 3, this will always be 'SoldierGraphics'.)
//			const orxCHAR* ObjectName = orxObject_GetName( orxOBJECT( currentEvent->hRecipient ) );

			// And finally the action which is this event.
			const orxCHAR* EventAct;

			switch( currentEvent->eID ) {
				case orxANIM_EVENT_START:
					EventAct = "started";
					break;
				case orxANIM_EVENT_STOP:
					EventAct = "stopped";
					break;
				case orxANIM_EVENT_CUT:
					EventAct = "been cut";
					break;
					//case orxANIM_EVENT_LOOP: EventAct = "looped"; break; // We comment this line out to avoid some hefty console spam.
				default:
					return orxSTATUS_SUCCESS; // Here we return early to avoid trying to access something we've not specifically set or loaded.
			}

			// Now we'll output this nicely to the console, so we can see exactly what animations
			//   are being called, on what objects, and what they're doing.
//			orxLOG("Animation <%s>@<%s> has %s!", EventPayload->zAnimName, ObjectName, EventAct );
			break;
		case orxEVENT_TYPE_INPUT:
			break;
	}

	return orxSTATUS_SUCCESS;
}
