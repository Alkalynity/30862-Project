#include "Base.h"
#include "Item.h"
#ifndef CONTAINER_H_
#define CONTAINER_H_

class Container : public Base {
public:
	char* accepts[100];
	char* items[100];

};

#endif