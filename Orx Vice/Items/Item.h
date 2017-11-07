//
//  Item.h
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 07/11/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#ifndef Item_h
#define Item_h

#include "orx.h"

class Item {
protected:
	orxSTRING name;
public:
	Item(orxSTRING);
	orxSTRING getName();
};

#endif
