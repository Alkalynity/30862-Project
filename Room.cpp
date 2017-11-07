#include "Room.h"

Room::Room(rapidxml::xml_node<>* node) {
	node = node->first_node();
	std::string node_name;
	std::string value;

	while (node != NULL) {
		if (node_name == (std::string)"name") {
			name = value;
		}
		else if (node_name == (std::string)"border") {
			Border* border = new Border(node); // CHECK THIS
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
		else if (node_name == (std::string)"type") {
			type = value;
		}

		node = node->next_sibling();
	}

}

Room::~Room() {

}