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
	// I don't know why I need to redeclare these, but VS won't compile if I don't
	std::string name;
	std::string description;
	std::string status;
	Container(rapidxml::xml_node<>*);
	virtual ~Container();
	std::vector<std::string>accepts;
	std::vector<std::string>items;
};

// for some reason I have to put the container constructor here or VS won't compile

Container::Container(rapidxml::xml_node<> * node) {
	node = node->first_node();
	std::string node_name;
	std::string value;

	while (node != NULL) {
		node_name = node->name();
		value = (std::string)node->value();

		if (node_name == (std::string)"name") {
			name = value;
		}

		else if (node_name == (std::string)"description") {
			description = value;
		}

		else if (node_name == (std::string)"status") {
			status = value;
		}

		// to do, add items, triggers, accepts
		node = node->next_sibling();
	}
}

#endif
