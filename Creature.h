#include "Base.h"
#ifndef CREATURE_H_
#define CREATURE_H_

class Creature : public Base {
public:
	char* vulnerability[100];
	Trigger* attack;

	Creature() {
		name = "NO NAME CREATURE";
		description = "NO DESCRIPTION";
		attack = NULL;
	}

};

#endif