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
			//needs to have a function to set up the turn on actions
			//turn_on = 0;
		}

		else if(node_name== (std::string)"status") {
			status = value;
		}
		else if(node_name == (std::string)"description") {
			description = value;
		}
		item_node = item_node -> next_sibling();

		// to do: turnon, triggers
	}
}

Item::~Item() {

}



