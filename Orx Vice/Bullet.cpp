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
}
