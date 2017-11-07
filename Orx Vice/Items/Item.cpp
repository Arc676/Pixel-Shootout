//
//  Item.cpp
//  Pixel Shootout
//
//  Created by Alessandro Vinciguerra on 07/11/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#include "Item.h"

Item::Item(const std::string &name) : name(name) {}

std::string Item::getName() {
	return name;
}
