#include "Room.h"

Room::Room(rapidxml::xml_node<>* node) {
	node = node->first_node();
	std::string node_name;
	std::string value;
	type = "regular";

	while (node != NULL) {
		node_name = node->name();
		value = (std::string)node->value();

		if (node_name == (std::string)"name") {
			name = value;
		}
		else if (node_name == (std::string)"border") {
			Border* border = new Border(node);
			borders.push_back(border);
		}
		else if (node_name == (std::string)"description") {
			description = value;
		}
		else if (node_name == (std::string)"status") {
			status = value;
		}
		else if (node_name == (std::string)"item") {
			items.push_back((std::string)value);
		}
		else if (node_name == (std::string)"container") {
			containers.push_back((std::string)value);
		}
		else if (node_name == (std::string)"creature") {
			creatures.push_back((std::string)value);
		}
		else if (node_name == (std::string)"type") {
			type = value;
		}
		else if (node_name == (std::string)"trigger") {
			Trigger* trigger = new Trigger(node);
			triggers.push_back(trigger);
		}

		node = node->next_sibling();
	}

}

Room::~Room() {

}
