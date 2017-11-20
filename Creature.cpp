#include "Creature.h"

Creature::Creature(rapidxml::xml_node<>*node) {
	node = node->first_node();
	std::string node_name;
	std::string value;
	attack = NULL;

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
		else if (node_name == (std::string)"trigger") {
			Trigger* trigger = new Trigger(node);
			triggers.push_back(trigger);
		}
		else if (node_name == (std::string)"attack") {
			Trigger* trigger = new Trigger(node);
			attack = trigger;
		}

		node = node->next_sibling();
	}

}

Creature::~Creature() {

}