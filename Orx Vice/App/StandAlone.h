//
//  StandAlone.h
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

#ifndef StandAlone_h
#define StandAlone_h

#include "orx.h"
#include "Player.h"
#include "Enemy.h"
#include "Environment.h"

class StandAlone {
public:
	static StandAlone* Instance();

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();

	static void orxFASTCALL Exit();

	static orxOBJECT* orxFASTCALL GetObjectByName(orxSTRING);

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);

	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT*);

	static orxVECTOR orxFASTCALL GetMouseWorldPosition();
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;
	static Player* player;
	static Environment* environment;
	static int paused;
	static orxOBJECT* deathScreen;
	static orxOBJECT* scoreLabel;
};

#endif /* StandAlone_h */
