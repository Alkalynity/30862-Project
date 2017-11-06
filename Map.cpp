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
/*
	Room* newRoom;
	while(rooms_nodes.size() != 0){
		newRoom = new Room(rooms_nodes.front());
		all_objects[newRoom -> name] = newRoom;
		rooms[newRoom -> name] = newRoom;
		rooms_nodes.pop();
	}
*/
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
/*
	Creature * newCreature;
	while(creatures_nodes.size() != 0){
		newCreature = new Room(creatures_nodes.front());
		all_objects[newCreature -> name] = newCreature;
		creatures[newCreature -> name] = newCreature;
		creatures_nodes.pop();
	}*/
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
	while(p != items.end()) {
		//std::cout<< p->first << std::endl;
		std::cout<< "Item name: " << p->second -> name << std::endl;
		std::cout << "Item writing:  " << p->second->writing << std::endl;
		++p;
	}
}

void Map::printCreatures() {

}

void Map::printContainers() {
	std::map<std::string, Container*>::iterator p = containers.begin();
	while (p != containers.end()) {
		std::cout << "Container name: " << p->second->name << std::endl;
		p++;
	}
}
