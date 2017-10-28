#include "Trigger.h"
#include <iostream>
#ifndef BASE_H_
#define BASE_H_

class Base {

public:
	char* name;
	char* status;
	char* description;
	Trigger* triggers[100];
};

#endif
