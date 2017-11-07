/*
 * Map.h
 *
 *  Created on: Nov 2, 2017
 *      Author: jcbar
 */

#ifndef MAP_H_
#define MAP_H_
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include "Item.h"
#include "Creature.h"
#include "Base.h"
#include "Room.h"
#include "Trigger.h"
#include <sstream>
#include <iterator>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Container.h"


class Map {
public:
	Map(std::string filename);
	virtual ~Map();
	std::map<std::string, Base*> all_objects;
	std::map<std::string, Item*> items;
	std::map<std::string, Container*> containers;
	std::map<std::string, Creature*> creatures;
	std::map<std::string, Room*> rooms;
	//map<char*, char*> lookup;
	void printItems();
	void printContainers();
	void printCreatures();
	void printRooms();
	void printTriggers(Trigger* trigger);

private:
	void createZorkMap(std::string filename);
	void fragmentXmlNodes(rapidxml::xml_node<>*, std::queue<rapidxml::xml_node<>*>&, std::queue<rapidxml::xml_node<> *>&, std::queue<rapidxml::xml_node<> *>&,std::queue<rapidxml::xml_node<> *>&);
};

#endif /* MAP_H_ */
