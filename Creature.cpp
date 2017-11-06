#include "Container.h"
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

		else if (node_name == (std::string)"item") { // check this
			items.push_back((std::string)value);
		}

		else if (node_name == (std::string)"accept") {
			accepts.push_back((std::string)value);
		}

		// to do: add triggers
		node = node->next_sibling();

	}
}

Container::~Container() {

}
