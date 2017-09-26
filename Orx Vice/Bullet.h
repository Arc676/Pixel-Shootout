//
//  Bullet.hpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 25/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "orx.h"

class Bullet {
	orxOBJECT *entity;

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);
public:
	Bullet(orxVECTOR, double, double);
};

#endif
