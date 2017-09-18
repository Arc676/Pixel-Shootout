//
//  Main.cpp
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#include "StandAlone.h"

int main(int argc, char* argv[]) {
	orx_Execute(argc, argv, StandAlone::Init, StandAlone::Run, StandAlone::Exit);
	return 0;
}
