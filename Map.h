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
	void printItems();
	void printInventory();
	void printContainers();
	void printCreatures();
	void printRooms();
	void printTriggers(Trigger* trigger);
	void run();

private:
	void createZorkMap(std::string filename);
	void setItemOwners();
	void fragmentXmlNodes(rapidxml::xml_node<>*, std::queue<rapidxml::xml_node<>*>&, std::queue<rapidxml::xml_node<> *>&, std::queue<rapidxml::xml_node<> *>&,std::queue<rapidxml::xml_node<> *>&);
	bool checkInput(std::string input);
	void checkTriggerConditions(Trigger* trigger);
	void executeTrigger(Trigger* trigger);
	void updateObject(std::string object_name, std::string status);
	void deleteObject(std::string object_name);
	void addObject(std::string object_name, std::string location_name);
	void openContainer(Container* container, Room* currRoom);
	void attackCreature(Creature* creature, Item* item);
	Trigger* checkRoomTriggers(std::string currRoom);
	std::string changeRoom(std::string command, std::string currRoom);
	int countWords(std::string input);
	std::vector<std::string> tokenizeString(std::string);
	Item* findItem(std::string name);
	Container* findContainer(std::string name);
	Creature* findCreature(std::string name);
	Room* findRoom(std::string name);
	Trigger* checkRoomTriggers(Room* current_room, std::string command);

};

#endif /* MAP_H_ */
