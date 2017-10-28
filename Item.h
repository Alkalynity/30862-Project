#include "Base.h"
#include "Conditions.h"
#ifndef ITEM_H_
#define ITEM_H_

class Item : public Base {
public:
	char* writing;
	Trigger* turn_on;
	char* owner;

	Item() {
		owner = "none";
		writing = "There is no writing on this item.";
		name = "NO NAME";
		status = "This item has no status.";
		description = "This item has no description.";
	}

	Item(const Item &item2) { // copy constructor
		writing = item2.writing;
		turn_on = item2.turn_on;
		owner = item2.owner;

		name = item2.name;
		status = item2.status;
		description = item2.description;

		// copies triggers array; I know it's severely unoptimized but w/e
		for (int i = 0; i <= 100; i++) {
			triggers[i] = item2.triggers[i];
		}
	}

};

#endif
