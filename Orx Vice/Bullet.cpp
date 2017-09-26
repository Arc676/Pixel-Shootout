//
//  Bullet.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 25/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#include "Bullet.h"

Bullet::Bullet(orxVECTOR pos, double speed, double angle) {
	orxConfig_Load("Entities.ini");
	entity = orxObject_CreateFromConfig("Bullet");

	orxVECTOR velocity = {(orxFLOAT)speed, 0};
	orxVector_2DRotate(&velocity, &velocity, (orxFLOAT)angle);

	orxObject_SetPosition(entity, &pos);
	orxObject_SetSpeed(entity, &velocity);

	orxObject_SetUserData(entity, this);

	orxCLOCK* clock = orxClock_Create(1, orxCLOCK_TYPE_USER);
	orxClock_Register(clock, Update, entity, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
}

void orxFASTCALL Bullet::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	orxOBJECT* obj = orxOBJECT(context);
	orxVECTOR pos;
	orxObject_GetPosition(obj, &pos);
	orxRender_GetScreenPosition(&pos, orxNULL, &pos);
	if (pos.fX < 0 || pos.fX > 1000 || pos.fY < 0 || pos.fY > 600) {
		orxObject_SetLifeTime(obj, 0);
	}
}
