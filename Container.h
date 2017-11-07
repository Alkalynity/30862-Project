#include "Base.h"
#include "Item.h"
#include<vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#ifndef CONTAINER_H_
#define CONTAINER_H_

class Container : public Base {
public:
	Container(rapidxml::xml_node<>*);
	virtual ~Container();
	std::vector<std::string>accepts;
	std::vector<std::string>items;
};

#endif