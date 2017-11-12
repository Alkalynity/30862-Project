/*
 * Map.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: jcbar
 */

#include "Map.h"

Map::Map(std::string filename) {
	createZorkMap(filename);
}

Map::~Map() {
}

void Map::createZorkMap(std::string filename) {
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * map_node;
	// read xml file into vector
	std::ifstream theFile(filename);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// parse buffer using xml file parsing library into doc
	doc.parse<0>(&buffer[0]);

	map_node = doc.first_node("map");

	std::queue<rapidxml::xml_node<> *> rooms_nodes;
	std::queue<rapidxml::xml_node<> *> items_nodes;
	std::queue<rapidxml::xml_node<> *> containers_nodes;
	std::queue<rapidxml::xml_node<> *> creatures_nodes;

	fragmentXmlNodes(map_node, rooms_nodes, items_nodes, containers_nodes, creatures_nodes);

	Room* newRoom;
	while(rooms_nodes.size() != 0){
		newRoom = new Room(rooms_nodes.front());
		all_objects[newRoom -> name] = newRoom;
		rooms[newRoom -> name] = newRoom;
		rooms_nodes.pop();
	}

	Item* newItem;
	while(items_nodes.size() != 0){
		newItem = new Item(items_nodes.front());
		all_objects[newItem -> name] = newItem;
		items[newItem -> name] = newItem;
		items_nodes.pop();
	}

	Container * newContainer;
	while(containers_nodes.size() != 0){
		newContainer = new Container(containers_nodes.front());
		all_objects[newContainer -> name] = newContainer;
		containers[newContainer -> name] = newContainer;
		containers_nodes.pop();
	}

	// set item owner field to container or room

	setItemOwners();

	Creature * newCreature;
	while(creatures_nodes.size() != 0){
		newCreature = new Creature(creatures_nodes.front());
		all_objects[newCreature -> name] = newCreature;
		creatures[newCreature -> name] = newCreature;
		creatures_nodes.pop();
	}
}

void Map::fragmentXmlNodes(rapidxml::xml_node<>* map_node, std::queue<rapidxml::xml_node<>*> &rooms, std::queue<rapidxml::xml_node<>*>&items, std::queue<rapidxml::xml_node<>*> &containers, std::queue<rapidxml::xml_node<>*> &creatures) {

	rapidxml::xml_node<>* node = map_node -> first_node();
	while(node != NULL){
		if((std::string)node->name() == (std::string)"room"){
			rooms.push(node);
		}
		else if((std::string)node -> name() == (std::string)"item") {
			items.push(node);
		}
		else if((std::string)node -> name() == (std::string)"container") {
			containers.push(node);
		}
		else if((std::string)node -> name() == (std::string)"creature") {
			creatures.push(node);
		}
		node = node -> next_sibling();
	}

}

void Map::run() {  // main loop for functionality of program
	std::string startRoom = "Entrance";
	std::string currRoom = startRoom;
	std::string input = "";
	std::vector<std::string> valid_direction = { "n", "s", "e", "w" };
	Trigger* trigger = NULL;
	

	bool game_over = false;
	bool trigger_override = false;

	std::cout << rooms.find(startRoom)->second->description << std::endl;
	
	while (!game_over) {
		std::getline(std::cin, input);
		std::string first_word = input.substr(0, input.find(" "));

		if (checkInput(input)) {
			trigger_override = false;
			std::cout << "Input valid." << std::endl;
			trigger = checkRoomTriggers(findRoom(currRoom), input);

			// if trigger != NULL, there is a trigger that overrides the given command

			if (trigger != NULL) {
				std::cout << "TRIGGER FOUND for command: " << input << std::endl;

				// check if trigger conditions are met
				// if so, override command and execute trigger

				checkTriggerConditions(trigger);
				if (trigger->conditions_met && (!(trigger->completed))) {
					executeTrigger(trigger);
					trigger_override = true;
				}
			}




			// if no trigger overrides command, execute command

			if (trigger_override == false) {
				for (std::vector<std::string>::iterator p = valid_direction.begin(); p != valid_direction.end(); ++p) {
					if ((*p) == input) {

					}
				}

				// print inventory

				if (input == (std::string)"i") {
					printInventory();
				}

				// open exit

				else if (input == (std::string)"open exit") {

				}

				// take [item]

				else if (first_word == (std::string)"take" && (countWords(input) == 2)) {
					std::vector<std::string> words = tokenizeString(input);
					Item* item = findItem(words.at(1));
					if (item != NULL) {
						if (item->owner == (std::string)"inventory") {
							std::cout << "You already have that." << std::endl;
						}
						else if (item->owner != rooms.find(currRoom)->second->name) {
							std::cout << "You can't take that." << std::endl;
						}
						else {
							std::cout << "You take the " << item->name << "." << std::endl;
							item->owner = "inventory";
						}
					}
					else {
						std::cout << "You can't take that." << std::endl;
					}
				}

				// open [container]

				else if (first_word == (std::string)"open" && input != (std::string)"open exit" && (countWords(input) == 2)) {

				}

				// read [item]

				else if (first_word == (std::string)"read" && (countWords(input) == 2)) {
					std::vector<std::string> words = tokenizeString(input);
					Item* item = findItem(words.at(1));
					if (item != NULL) {
						if (item->owner != (std::string)"inventory") {
							std::cout << "You don't have that item." << std::endl;
						}
						else {
							std::cout << item->writing << std::endl;
						}
					}
					else {
						std::cout << "You don't have that item." << std::endl;
					}

				}

				// drop [item]

				else if (first_word == (std::string)"drop" && (countWords(input) == 2)) {

				}

				// put [item] in [container]

				else if (first_word == (std::string)"put" && (countWords(input) == 4) && input.find(" in ") != std::string::npos) {

				}

				// turn on [item]

				else if (input.find("turn on") != std::string::npos && first_word == (std::string)"turn" && (countWords(input) == 3)) {

				}

				// attack [creature] with [item]

				else if (first_word == (std::string)"attack" && (countWords(input) == 4) && input.find(" with ") != std::string::npos) {

				}

			}
		}
		else {
			std::cout << "Invalid input." << std::endl;
		}
	}

}

bool Map::checkInput(std::string input) {
	std::vector<std::string> valid_direction = {"n", "s", "e", "w"};
	std::string first_word = input.substr(0, input.find(" "));
	
	// check if directional input

	for (std::vector<std::string>::iterator p = valid_direction.begin(); p != valid_direction.end(); ++p) {
		if ((*p) == input) {
			return true;
		}
	}

	// check if "check inventory"

	if (input == (std::string)"i") {
		return true;
	}

	// check if "open exit"

	else if (input == (std::string)"open exit") {
		return true;
	}

	// check if "take"

	else if (first_word == (std::string)"take" && (countWords(input) == 2)) {
		return true;
	}

	// check if "open"

	else if (first_word == (std::string)"open" && input != (std::string)"open exit" && (countWords(input) == 2)) {
		return true;
	}

	// check if "read"

	else if (first_word == (std::string)"read" && (countWords(input) == 2)) {
		return true;
	}

	// check if "drop"

	else if (first_word == (std::string)"drop" && (countWords(input) == 2)) {
		return true;
	}

	// check if "put"

	else if (first_word == (std::string)"put" && (countWords(input) == 4) && input.find(" in ") != std::string::npos) {
		return true;
	}

	// check if "turn on"

	else if (input.find("turn on") != std::string::npos && first_word == (std::string)"turn" && (countWords(input) == 3)) {
		return true;
	}

	// check if "attack"

	else if (first_word == (std::string)"attack" && (countWords(input) == 4) && input.find(" with ") != std::string::npos) {
		return true;
	}

	return false;
}

int Map::countWords(std::string input)
{
	int number_of_words = 1;
	for (int i = 0; i < input.length(); i++)
		if (input[i] == ' ')
			number_of_words++;
	return number_of_words;
}

void Map::printInventory() {
	bool inv_empty = true;
	std::cout << "Inventory: ";
	for (std::map<std::string, Item*>::iterator p = items.begin(); p != items.end(); ++p) {
		if (p->second->owner == (std::string)"inventory") {
			if (inv_empty != true) {
				std::cout << ", ";
			}
			std::cout << p->second->name;
			inv_empty = false;
		}
	}

	if (inv_empty == true) {
		std::cout << "empty" << std::endl;
	}

}

void Map::printItems() {
	std::map<std::string, Item*>::iterator p = items.begin();
	std::cout << "///// ITEMS /////" << std::endl;
	while(p != items.end()) {
		//std::cout<< p->first << std::endl;
		std::cout<< "Item name: " << p->second -> name << std::endl;
		std::cout << "Item writing:  " << p->second->writing << std::endl;
		std::cout << "Item status: " << p->second->status << std::endl;
		if (p->second->turn_on != NULL) {
			std::cout << "Item turnon: " << std::endl;
			printTriggers(p->second->turn_on);
		}
		// print triggers vector
		std::cout << "Triggers: " << std::endl;
		for (std::vector<Trigger*>::iterator q = p->second->triggers.begin(); q != p->second->triggers.end(); ++q) {
			printTriggers(*q);
		}
		std::cout << std::endl;

		++p;
	}
}

void Map::printCreatures() {
	std::map<std::string, Creature*>::iterator p = creatures.begin();
	std::cout << "\n///// CREATURES /////" << std::endl;
	while (p != creatures.end()) {
		std::cout << "Creature name: " << p->second->name << std::endl;
		// print vulnerabilities vector
		std::cout << "Vulnerability: ";
		for (std::vector<std::string>::iterator q = p->second->vulnerabilities.begin(); q != p->second->vulnerabilities.end(); ++q) {
			std::cout << *q;
		}
		std::cout << std::endl;
		// print triggers vector
		std::cout << "Triggers: " << std::endl;
		for (std::vector<Trigger*>::iterator q = p->second->triggers.begin(); q != p->second->triggers.end(); ++q) {
			printTriggers(*q);
		}
		// print attack
		std::cout << "Attack: " << std::endl;
		printTriggers(p->second->attack);
		std::cout << std::endl;
		++p;
	}
}

void Map::printRooms() {
	std::map<std::string, Room*>::iterator p = rooms.begin();
	std::cout << "\n///// ROOMS /////" << std::endl;
	while (p != rooms.end()) {
		std::cout << "Room name:" << p->second->name << std::endl;
		std::cout << "Type: " << p->second->type << std::endl;
		// print items vector
		std::cout << "Items: ";
		for (std::vector<std::string>::iterator q = p->second->items.begin(); q != p->second->items.end(); ++q) {
			std::cout << *q << " ";
		}
		std::cout << std::endl;
		// print containers vector
		std::cout << "Containers: ";
		for (std::vector<std::string>::iterator q = p->second->containers.begin(); q != p->second->containers.end(); ++q) {
			std::cout << *q << " ";
		}
		std::cout << std::endl;
		// print creatures vector
		std::cout << "Creatures: ";
		for (std::vector<std::string>::iterator q = p->second->creatures.begin(); q != p->second->creatures.end(); ++q) {
			std::cout << *q << " ";
		}
		std::cout << std::endl;
		// print borders vector
		std::cout << "Borders: " << std::endl;
		std::string name;
		for (std::vector<Border*>::iterator q = p->second->borders.begin(); q != p->second->borders.end(); ++q) {
			std::cout << (*q)->name << " to the " << (*q)->direction << std::endl;		
		}
		// print triggers vector
		std::cout << "Triggers: " << std::endl;
		for (std::vector<Trigger*>::iterator q = p->second->triggers.begin(); q != p->second->triggers.end(); ++q) {
			printTriggers(*q);
		}
		std::cout << std::endl;
		p++;
	}
}

void Map::printContainers() {
	std::map<std::string, Container*>::iterator p = containers.begin();
	std::cout << "///// CONTAINERS /////" << std::endl;
	while (p != containers.end()) {
		std::cout << "Container name: " << p->second->name << std::endl;
		std::cout << "Items: ";
		std::cout << "Container status: " << p->second->status << std::endl;
		// print items vector
		for (std::vector<std::string>::iterator q = p->second->items.begin(); q != p->second->items.end(); ++q) {
			std::cout << *q << " ";
		}
		// print accept vector
		std::cout << "\nAccepts: ";
		for (std::vector<std::string>::iterator q = p->second->accepts.begin(); q != p->second->accepts.end(); ++q) {
			std::cout << *q << " ";
		}
		std::cout << "\n";
		// print triggers vector
		std::cout << "Triggers: " << std::endl;
		for (std::vector<Trigger*>::iterator q = p->second->triggers.begin(); q != p->second->triggers.end(); ++q) {
			printTriggers(*q);
		}
		p++;
	}
}

void Map::printTriggers(Trigger* trigger) {
	if (trigger->command != "") {
		std::cout << "Command: " << trigger->command << std::endl;
	}
	if (trigger->type != "") {
		std::cout << "Type: " << trigger->type << std::endl;
	}
	std::cout << "Print: ";
	for (std::vector<std::string>::iterator q = trigger->print.begin(); q != trigger->print.end(); ++q) {
		std::cout << *q << "; ";
	}
	std::cout << std::endl;
	std::cout << "Actions: ";
	for (std::vector<std::string>::iterator q = trigger->action.begin(); q != trigger->action.end(); ++q) {
		std::cout << *q << "; ";
	}
	std::cout << std::endl;
	std::cout << "CONDITIONS: " << std::endl;
	for (std::vector<Condition*>::iterator q = trigger->conditions.begin(); q != trigger->conditions.end(); ++q) {
		if ((*q)->owner != "") {
			std::cout << "owner: " << (*q)->owner << std::endl;
		}
		if ((*q)->has != "") {
			std::cout << "has: " << (*q)->has << std::endl;
		}
		if ((*q)->object != "") {
			std::cout << "object: " << (*q)->object << std::endl;
		}
		if ((*q)->status != "") {
			std::cout << "status: " << (*q)->status << std::endl;
		}
	}
	std::cout << std::endl;

}

Item* Map::findItem(std::string name) {
	std::map<std::string, Item*>::iterator p = items.begin();
	while (p != items.end()) {
		if (p->second->name == name) {
			return (p->second);
		}
		p++;
	}
	return NULL;
}

Container* Map::findContainer(std::string name) {
	std::map<std::string, Container*>::iterator p = containers.begin();
	while (p != containers.end()) {
		if (p->second->name == name) {
			return (p->second);
		}
		p++;
	}
	return NULL;
}

Creature* Map::findCreature(std::string name) {
	std::map<std::string, Creature*>::iterator p = creatures.begin();
	while (p != creatures.end()) {
		if (p->second->name == name) {
			return (p->second);
		}
		p++;
	}
	return NULL;
}

Room* Map::findRoom(std::string name) {
	std::map<std::string, Room*>::iterator p = rooms.begin();
	while (p != rooms.end()) {
		if (p->second->name == name) {
			return (p->second);
		}
		p++;
	}
	return NULL;
}

Trigger* Map::checkRoomTriggers(Room* current_room, std::string command) {
	Item* item = NULL;
	Container* container = NULL;
	Creature* creature = NULL;
	Trigger* found_trigger = NULL;

	// if function finds trigger that matches the command, it returns the trigger
	// otherwise, returns NULL

	found_trigger = current_room->checkTriggers(command);
	if (found_trigger != NULL) {
		return found_trigger;
	}

	for (std::vector<std::string>::iterator q = current_room->items.begin(); q != current_room->items.end(); ++q) {
		item = findItem(*q);
		found_trigger = item->checkTriggers(command);
		if (found_trigger != NULL) {
			return found_trigger;
		}
	}
	for (std::vector<std::string>::iterator q = current_room->containers.begin(); q != current_room->containers.end(); ++q) {
		container = findContainer(*q);
		found_trigger = container->checkTriggers(command);
		if (found_trigger != NULL) {
			return found_trigger;
		}
	}
	for (std::vector<std::string>::iterator q = current_room->creatures.begin(); q != current_room->creatures.end(); ++q) {
		creature = findCreature(*q);
		found_trigger = creature->checkTriggers(command);
		if (found_trigger != NULL) {
			return found_trigger;
		}
	}
	return NULL;
}

void Map::setItemOwners() {
	Item* item = NULL;
	for (std::map<std::string, Room*>::iterator p = rooms.begin(); p != rooms.end(); ++p) {
		for (std::vector<std::string>::iterator q = p->second->items.begin(); q != p->second->items.end(); ++q) {
			item = findItem((*q));
			item->owner = p->second->name;
		}
	}
	for (std::map<std::string, Container*>::iterator p = containers.begin(); p != containers.end(); ++p) {
		for (std::vector<std::string>::iterator q = p->second->items.begin(); q != p->second->items.end(); ++q) {
			item = findItem((*q));
			item->owner = p->second->name;
		}
	}

}

void Map::checkTriggerConditions(Trigger* trigger) {
	if (trigger == NULL) {
		return;
	}
	if (trigger->conditions.size() == 0) {
		trigger->conditions_met = true;
		return;
	}
	for (std::vector<Condition*>::iterator p = trigger->conditions.begin(); p != trigger->conditions.end(); ++p ) {
		// Case 1: [Object] is [status]
		if ((*p)->status != (std::string)"") {
			
		}

		// Case 2: [Container/Inventory] has [Object]
		// I'm assuming here that the only two things that can "own" an object are the inventory or a container
		// If this isn't true, then this will have to be changed
		else if ((*p)->owner != (std::string)"") {
			Item* item = findItem((*p)->object);
			if (item == NULL) {
				std::cout << "ERROR: ITEM NOT FOUND" << std::endl;
				return;
			}
			if ((*p)->owner == (std::string)"inventory") {
				if (item->owner == (std::string)"inventory") {
					if ((*p)->has == (std::string)"no") {
						trigger->conditions_met = false;
						return;
					}
					else if ((*p)->has == (std::string)"yes") {
						trigger->conditions_met = true;
					}

				}
				else {
					if ((*p)->has == (std::string)"no") {
						trigger->conditions_met = true;
					}
					else if ((*p)->has == (std::string)"yes") {
						trigger->conditions_met = false;
						return;
					}
				}
			}
			else {
				Container* owner = findContainer((*p)->owner);
				if (owner == NULL) {
					std::cout << "ERROR: OWNER NOT FOUND" << std::endl;
					return;
				}
				if (item->owner == owner->name) {
					if ((*p)->has == (std::string)"no") {
						trigger->conditions_met = false;
						return;
					}
					else {
						trigger->conditions_met = true;
					}
				}
				else {
					if ((*p)->has == (std::string)"no") {
						trigger->conditions_met = true;
					}
					else {
						trigger->conditions_met = false;
						return;
					}
				}
			}

		}
	}
}

std::vector<std::string> Map::tokenizeString(std::string string) {
	std::stringstream ss(string);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

void Map::executeTrigger(Trigger* trigger) {

	for (std::vector<std::string>::iterator p = trigger->print.begin(); p != trigger->print.end(); ++p) {
		std::cout << (*p) << std::endl;
	}

	for (std::vector<std::string>::iterator p = trigger->action.begin(); p != trigger->action.end(); ++p) {
		// do this later
	}

	if (trigger->type == "single") {
		trigger->completed = true;
	}
}