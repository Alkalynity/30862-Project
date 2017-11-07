#include "Trigger.h"

Trigger::Trigger(rapidxml::xml_node<>* node) {
	node = node->first_node();
	std::string node_name;
	std::string value;
	type = "single";
	command = "";

	while (node != NULL) {
		node_name = node->name();
		value = (std::string)node->value();

		if (node_name == (std::string)"type") {
			type = (std::string)value;
		}
		else if (node_name == (std::string)"command") {
			command = (std::string)value;
		}
		else if (node_name == (std::string)"print") {
			print.push_back((std::string)value);
		}
		else if (node_name == (std::string)"action") {
			action.push_back((std::string)value);
		}
		else if (node_name == (std::string)"condition") {
			Condition* condition = new Condition(node);
			conditions.push_back(condition);
		}
		node = node->next_sibling();
	}
}

Trigger::~Trigger() {

}