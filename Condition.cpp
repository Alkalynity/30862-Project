#include "Condition.h"

Condition::Condition(rapidxml::xml_node<>* node) {
	node = node->first_node();
	std::string node_name;
	std::string value;
	has = "";
	object = "";
	owner = "";
	status = "";

	while (node != NULL) {
		if (node_name == (std::string)"has") {
			has = (std::string)value;
		}
		else if (node_name == (std::string)"object") {
			object = (std::string)value;
		}
		else if (node_name == (std::string)"owner") {
			owner = (std::string)value;
		}
		else if (node_name == (std::string)"status") {
			status = (std::string)value;
		}
		node = node->next_sibling();
	}

}

Condition::~Condition() {

}