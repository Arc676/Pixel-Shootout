//
//  StandAlone.h
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#ifndef StandAlone_h
#define StandAlone_h

#include <string>
#include "orx.h"

class StandAlone {
public:
	static StandAlone* Instance();

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();

	static void orxFASTCALL Exit();

	static orxOBJECT* orxFASTCALL GetObjectByName(std::string);

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);

	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT*);

	static orxVECTOR orxFASTCALL GetMouseWorldPosition();
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;
};

#endif /* StandAlone_h */
