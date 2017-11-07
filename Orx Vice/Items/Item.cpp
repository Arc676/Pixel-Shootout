//
//  Item.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 07/11/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#include "Item.h"

Item::Item(orxSTRING name) : name(name) {}

orxSTRING Item::getName() {
	return name;
}
