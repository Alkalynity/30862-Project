#include "Creature.h"

Creature::Creature(rapidxml::xml_node<>*node) {
	std::string node_name;
	std::string value;

	node_name = node->name();
	value = node->value();
	int i = 0; // vulnerabilities iterator

	while (node != NULL) {
		if (node_name == (std::string)"name") {
			name = value;
		}

		if (node_name == (std::string)"description") {
			description = value;
		}

		else if (node_name == (std::string)"status") {
			status = value;
		}

		else if (node_name == (std::string)"vulnerabilities") {
			vulnerabilities[i] = value;
			i++;
		}

		// to do: load triggers, attack
	}
	node = node->next_sibling();
}