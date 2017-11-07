#ifndef ROOM_H_
#define ROOM_H_
#include "Base.h"
#include "Item.h"
#include "Border.h"

class Room : public Base {
public:
	Room(rapidxml::xml_node<>*);
	~Room();
	std::string type;
	std::vector<Border*> borders;
	std::vector<std::string> creatures;
	std::vector<std::string> containers;
	std::vector<std::string> items;
};

#endif