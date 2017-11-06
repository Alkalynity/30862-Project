#include "Base.h"
#include "Item.h"
#include<vector>
#ifndef CONTAINER_H_
#define CONTAINER_H_

class Container : public Base {
public:
	std::vector<std::string>accepts;
	std::vector<std::string>items;
};

#endif
