#include "Creature.h"

Creature::Creature(rapidxml::xml_node<>*node) {
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

		else if (node_name == (std::string)"vulnerability") {
			vulnerabilities.push_back((std::string)value);
		}

		// to do: load triggers, attack

		node = node->next_sibling();
	}

}

Creature::~Creature() {

}