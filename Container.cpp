#include "Container.h"
Container::Container(rapidxml::xml_node<> * node) {
	node = node->first_node();
	std::string node_name;
	std::string value;
	description = "No description.";
	name = "NO NAME";
	status = "";

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
		else if (node_name == (std::string)"item") {
			items.push_back((std::string)value);
		}
		else if (node_name == (std::string)"accept") {
			accepts.push_back((std::string)value);
		}
		else if (node_name == (std::string)"trigger") {
			Trigger* trigger = new Trigger(node);
			triggers.push_back(trigger);
		}
		node = node->next_sibling();

	}
}

Container::~Container() {

}