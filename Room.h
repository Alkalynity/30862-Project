#include "Base.h"
#include "Border.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"

#ifndef ROOM_H_
#define ROOM_H_

class Room : public Base {
public:
	char* type;
	Border* borders[100];
	char* creatures[100];
	char* containers[100];
	char* items[100];

	Room() {
		borders[0] = NULL;
		creatures[0] = NULL;
		containers[0] = NULL;
		items[0] = NULL;
	}

};

#endif