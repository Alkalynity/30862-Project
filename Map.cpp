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
	std::ifstream theFile("xml_test.xml");
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

void Map::printItems() {
	std::map<std::string, Item*>::iterator p = items.begin();
	std::cout << "///// ITEMS /////" << std::endl;
	while(p != items.end()) {
		//std::cout<< p->first << std::endl;
		std::cout<< "Item name: " << p->second -> name << std::endl;
		std::cout << "Item writing:  " << p->second->writing << std::endl;
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
