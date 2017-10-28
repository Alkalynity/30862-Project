#ifndef TRIGGER_H_
#define TRIGGER_H_
#include "Conditions.h"

class Trigger {
public:
	char* command;
	char* print;
	char* action[100];
	char* type;

	Trigger() {
		command = NULL;
		print = NULL;
		type = "single"; // type is, by default, single
	}

	Condition* conditions[100];

	// this class probably needs a lot of work

};

#endif