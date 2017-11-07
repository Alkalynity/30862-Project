/*
 * Item.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: jcbar
 */
#include"Item.h"

Item::Item(rapidxml::xml_node<> * item_node){
	item_node = item_node -> first_node();

	std::string node_name;
	std::string value;
	writing = "Item has no writing.";
	name = "NO NAME";
	description = "Item has no description.";
	status = "";

	while(item_node != 0) {
		node_name = item_node -> name();
		value = item_node -> value();

		if(node_name == (std::string)"name") {
			name = value;
		}

		else if(node_name == (std::string)"writing") {
			writing = value;
		}
		else if(node_name == (std::string)"turnon") {
			Trigger* trigger = new Trigger(item_node);
			turn_on = trigger;
		}

		else if(node_name== (std::string)"status") {
			status = value;
		}
		else if(node_name == (std::string)"description") {
			description = value;
		}
		else if (node_name == (std::string)"trigger") {
			Trigger* trigger = new Trigger(item_node);
			triggers.push_back(trigger);
		}

		item_node = item_node -> next_sibling();

	}
}

Item::~Item() {

}



