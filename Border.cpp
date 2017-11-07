#include "Border.h"

Border::Border(rapidxml::xml_node<>* node) {
	node = node->first_node();
	std::string node_name;
	std::string value;

	while (node != NULL) {
		if (node_name == (std::string)"name") {
			name = value;
		}
		else if (node_name == (std::string)"direction") {
			direction = value;
		}
		node = node->next_sibling();
	}
}

Border::~Border() {

}