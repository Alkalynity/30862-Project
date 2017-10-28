#include <iostream>
#ifndef CONDITIONS_H_
#define CONDITIONS_H_
class Condition {
public:
	char* has;
	char* object;
	char* owner;
	char* status;

	Condition() {
		has = NULL;
		object = NULL;
		owner = NULL;
		status = NULL;
	}

};
#endif