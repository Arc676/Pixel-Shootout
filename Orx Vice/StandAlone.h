//
//  StandAlone.h
//  Orx Vice
//
//  Created by Alessandro Vinciguerra on 18/09/2017.
//  Copyright © 2017 Arc676. All rights reserved.
//

#ifndef StandAlone_h
#define StandAlone_h

#include "orx.h"

class StandAlone {
public:
	static StandAlone* Instance();
	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void orxFASTCALL Exit();
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;
};

#endif /* StandAlone_h */
