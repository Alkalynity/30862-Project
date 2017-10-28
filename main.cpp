// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "Base.h"
#include "Item.h"
#include "Room.h"
#include "Border.h"
#include "Trigger.h"
#include "Creature.h"
#include "Container.h"
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <fstream>
#include <sstream>


int main() {
	std::cout << "parsing xml file..." << std::endl;
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * map;
	// read xml file into vector
	std::ifstream theFile("xml_test.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// parse buffer using xml file parsing library into doc
	doc.parse<0>(&buffer[0]);

	map = doc.first_node("map");

	// all rooms in XML file are added to a Rooms* array, all items are loaded into an Items* array, etc...

	Room* rooms[100];
	Item* items[100];
	Container* containers[100];
	Creature* creatures[100];
	int k = 0;

	// load item data

	std::cout << "\nITEMS: " << std::endl;

	for (rapidxml::xml_node<> * item_loop = map->first_node("item"); item_loop; item_loop = item_loop->next_sibling("item")) {
		Item* temp = new Item();
		if (item_loop->first_node("name")) {
			temp->name = item_loop->first_node("name")->value();
			std::cout << "Item name: " << temp->name << std::endl;
		}

		if (item_loop->first_node("writing")) {
			temp->writing = item_loop->first_node("writing")->value();
			std::cout << "Writing: " << temp->writing << std::endl;
		}

		if (item_loop->first_node("description")) {
			temp->description = item_loop->first_node("description")->value();
			std::cout << "Description: " << temp->description << std::endl;
		}

		if (item_loop->first_node("status")) {
			temp->status = item_loop->first_node("status")->value();
			std::cout << "Status: " << temp->status << std::endl;
		}

		// load turnon item data

		if (item_loop->first_node("turnon")) {
			rapidxml::xml_node<> * turnon_node = item_loop->first_node("turnon");
			Trigger* turn_on = new Trigger();
			int j = 0;
			std::cout << "Turn on info: " << std::endl;

			if (turnon_node->first_node("print")) {
				turn_on->print = turnon_node->first_node("print")->value();
				std::cout << "Print: " << turn_on->print << std::endl;
			}

			j = 0;
			std::cout << "Actions: ";
			for (rapidxml::xml_node<> * action_node = turnon_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
				turn_on->action[j] = action_node->value();
				std::cout << turn_on->action[j] << " ";
				j++;
			}
			std::cout << '\n';

			int i = 0;

			// load conditions for turnon

			for (rapidxml::xml_node<> * condition_node = turnon_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
				Condition* condition = new Condition();
				std::cout << "Conditions for turn on..." << std::endl;
				if (condition_node->first_node("has")) {
					condition->has = condition_node->first_node("has")->value();
					std::cout << "\thas:" << condition->has << std::endl;
				}

				if (condition_node->first_node("object")) {
					condition->object = condition_node->first_node("object")->value();
					std::cout << "\tobject:" << condition->object << std::endl;
				}

				if (condition_node->first_node("owner")) {
					condition->owner = condition_node->first_node("owner")->value();
					std::cout << "\towner:" << condition->owner << std::endl;
				}

				if (condition_node->first_node("status")) {
					condition->status = condition_node->first_node("status")->value();
					std::cout << "\tstatus:" << condition->status << std::endl;
				}

				turn_on->conditions[i] = condition;
				i++;

			}
			temp->turn_on = turn_on;
		}

		// load item triggers
		int i = 0;
		for (rapidxml::xml_node<> * trigger_node = item_loop->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
			std::cout << "Item triggers..." << std::endl;
			Trigger* trigger = new Trigger();
			int j = 0;

			if (trigger_node->first_node("command")) {
				trigger->command = trigger_node->first_node("command")->value();
				std::cout << "Command: " << trigger->command << std::endl;
			}

			if (trigger_node->first_node("print")) {
				trigger->print = trigger_node->first_node("print")->value();
				std::cout << "Print: " << trigger->print << std::endl;
			}

			// load actions[]
			j = 0;
			std::cout << "Actions: ";
			for (rapidxml::xml_node<> * action_node = item_loop->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
				trigger->action[j] = action_node->value();
				std::cout << trigger->action[j] << " ";
				j++;
			}
			std::cout << '\n';


			// load conditions for item triggers

			j = 0;
			for (rapidxml::xml_node<> * condition_node = trigger_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
				Condition* condition = new Condition();
				std::cout << "Conditions for trigger..." << std::endl;
				if (condition_node->first_node("has")) {
					condition->has = condition_node->first_node("has")->value();
					std::cout << "\thas:" << condition->has << std::endl;
				}

				if (condition_node->first_node("object")) {
					condition->object = condition_node->first_node("object")->value();
					std::cout << "\tobject:" << condition->object << std::endl;
				}

				if (condition_node->first_node("owner")) {
					condition->owner = condition_node->first_node("owner")->value();
					std::cout << "\towner:" << condition->owner << std::endl;
				}

				if (condition_node->first_node("status")) {
					condition->status = condition_node->first_node("status")->value();
					std::cout << "\tstatus:" << condition->status << std::endl;
				}

				trigger->conditions[j] = condition;
				j++;

			}

			temp->triggers[i] = trigger;
			i++;
		}

		items[k] = temp;
		k++;
	}

	// load container data

	k = 0;
	std::cout << "\nCONTAINERS:" << std::endl;
	for (rapidxml::xml_node<> * container_node = map->first_node("container"); container_node; container_node = container_node->next_sibling("container")) {
		Container* container = new Container();
		if (container_node->first_node("name")) {
			container->name = container_node->first_node("name")->value();
			std::cout << "Name: " << container->name << std::endl;
		}

		if (container_node->first_node("status")) {
			container->status = container_node->first_node("status")->value();
			std::cout << "Status: " << container->status << std::endl;
		}

		if (container_node->first_node("description")) {
			container->description = container_node->first_node("description")->value();
			std::cout << "Description: " << container->description << std::endl;
		}

		// load in accepts[] array
		int i = 0;

		for (rapidxml::xml_node<> * accept_loop = container_node->first_node("accept"); accept_loop; accept_loop = accept_loop->next_sibling("accept")) {
			std::cout << "Accepts: ";
			container->accepts[i] = accept_loop->value();
			std::cout << container->accepts[i] << " ";
			i++;
		}
		std::cout << '\n';

		// load in items[] array

		i = 0;
		std::cout << "Items: ";
		for (rapidxml::xml_node<> * items = container_node->first_node("item"); items; items = items->next_sibling("item")) {
			container->items[i] = items->value();
			std::cout << container->items[i] << " ";
			i++;
		}
		std::cout << '\n';

		// load in triggers[] array

		i = 0;
		for (rapidxml::xml_node<> * trigger_node = container_node->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
			std::cout << "Container triggers..." << std::endl;
			Trigger* trigger = new Trigger();
			int j = 0;

			if (trigger_node->first_node("command")) {
				trigger->command = trigger_node->first_node("command")->value();
				std::cout << "Command: " << trigger->command << std::endl;
			}

			if (trigger_node->first_node("print")) {
				trigger->print = trigger_node->first_node("print")->value();
				std::cout << "Print: " << trigger->print << std::endl;
			}

			if (trigger_node->first_node("action")) {
				j = 0;
				std::cout << "Actions: ";
				for (rapidxml::xml_node<> * action_node = trigger_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
					trigger->action[j] = action_node->value();
					std::cout << trigger->action[j] << " ";
					j++;
				}
				std::cout << '\n';

				// load conditions for container triggers

				j = 0;
				for (rapidxml::xml_node<> * condition_node = trigger_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
					Condition* condition = new Condition();
					std::cout << "Conditions for trigger..." << std::endl;
					if (condition_node->first_node("has")) {
						condition->has = condition_node->first_node("has")->value();
						std::cout << "\thas:" << condition->has << std::endl;
					}

					if (condition_node->first_node("object")) {
						condition->object = condition_node->first_node("object")->value();
						std::cout << "\tobject:" << condition->object << std::endl;
					}

					if (condition_node->first_node("owner")) {
						condition->owner = condition_node->first_node("owner")->value();
						std::cout << "\towner:" << condition->owner << std::endl;
					}

					if (condition_node->first_node("status")) {
						condition->status = condition_node->first_node("status")->value();
						std::cout << "\tstatus:" << condition->status << std::endl;
					}

					trigger->conditions[j] = condition;
					j++;
				}
				container->triggers[i] = trigger;
				i++;
			}
			containers[k] = container;
			k++;
		}
	}

	// load creature data

	k = 0;
	std::cout << "\nCREATURES: " << std::endl;
	for (rapidxml::xml_node<> * creature_node = map->first_node("creature"); creature_node; creature_node = creature_node->next_sibling("creature")) {
		Creature* creature = new Creature();

		// get name, desc, status

		if (creature_node->first_node("name")) {
			creature->name = creature_node->first_node("name")->value();
			std::cout << "Name: " << creature->name << std::endl;
		}

		if (creature_node->first_node("description")) {
			creature->description = creature_node->first_node("description")->value();
			std::cout << "Description: " << creature->description << std::endl;
		}

		if (creature_node->first_node("status")) {
			creature->status = creature_node->first_node("status")->value();
			std::cout << "Status: " << creature->status << std::endl;
		}

		// load vulnerability[]

		int i = 0;

		std::cout << "Vulnerability: ";
		for (rapidxml::xml_node<> * vul_node = creature_node->first_node("vulnerability"); vul_node; vul_node = vul_node->next_sibling("vulnerability")) {
			creature->vulnerability[i] = vul_node->value();
			std::cout << creature->vulnerability[i] << " ";
			i++;
		}
		std::cout << '\n';
		creatures[k] = creature;
		k++;

		// load triggers[]

		i = 0;
		for (rapidxml::xml_node<> * trigger_node = creature_node->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
			std::cout << "Creature triggers..." << std::endl;
			Trigger* trigger = new Trigger();
			int j = 0;

			if (trigger_node->first_node("command")) {
				trigger->command = trigger_node->first_node("command")->value();
				std::cout << "Command: " << trigger->command << std::endl;
			}

			if (trigger_node->first_node("print")) {
				trigger->print = trigger_node->first_node("print")->value();
				std::cout << "Print: " << trigger->print << std::endl;
			}

			// load trigger actions

			if (trigger_node->first_node("action")) {
				j = 0;
				std::cout << "Actions: ";
				for (rapidxml::xml_node<> * action_node = trigger_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
					trigger->action[j] = action_node->value();
					std::cout << trigger->action[j] << " ";
					j++;
				}
				std::cout << '\n';
			}
			// load conditions for creature triggers

			j = 0;
			for (rapidxml::xml_node<> * condition_node = trigger_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
				Condition* condition = new Condition();
				std::cout << "Conditions for trigger..." << std::endl;
				if (condition_node->first_node("has")) {
					condition->has = condition_node->first_node("has")->value();
					std::cout << "\thas:" << condition->has << std::endl;
				}

				if (condition_node->first_node("object")) {
					condition->object = condition_node->first_node("object")->value();
					std::cout << "\tobject:" << condition->object << std::endl;
				}

				if (condition_node->first_node("owner")) {
					condition->owner = condition_node->first_node("owner")->value();
					std::cout << "\towner:" << condition->owner << std::endl;
				}

				if (condition_node->first_node("status")) {
					condition->status = condition_node->first_node("status")->value();
					std::cout << "\tstatus:" << condition->status << std::endl;
				}

				trigger->conditions[j] = condition;
				j++;
			}
			creature->triggers[i] = trigger;
			i++;
		}


		// load attack
		std::cout << "Attack data... " << std::endl;
		if (creature_node->first_node("attack")) {
			Trigger* attack = new Trigger();
			int i = 0;
			rapidxml::xml_node<> * attack_node = creature_node->first_node("attack");

			if (attack_node->first_node("print")) {
				attack->print = attack_node->first_node("print")->value();
				std::cout << "Prints: " << attack->print << std::endl;
			}

			// load actions for attack

			if (attack_node->first_node("action")) {
				int j = 0;
				std::cout << "Actions: ";
				for (rapidxml::xml_node<> * action_node = attack_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
					attack->action[j] = action_node->value();
					std::cout << attack->action[j] << " ";
					j++;
				}
				std::cout << '\n';

				// load conditions for attack

				for (rapidxml::xml_node<> * condition_node = attack_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
					Condition* condition = new Condition();
					std::cout << "Conditions for attack..." << std::endl;
					if (condition_node->first_node("has")) {
						condition->has = condition_node->first_node("has")->value();
						std::cout << "\thas:" << condition->has << std::endl;
					}

					if (condition_node->first_node("object")) {
						condition->object = condition_node->first_node("object")->value();
						std::cout << "\tobject:" << condition->object << std::endl;
					}

					if (condition_node->first_node("owner")) {
						condition->owner = condition_node->first_node("owner")->value();
						std::cout << "\towner:" << condition->owner << std::endl;
					}

					if (condition_node->first_node("status")) {
						condition->status = condition_node->first_node("status")->value();
						std::cout << "\tstatus:" << condition->status << std::endl;
					}

					attack->conditions[i] = condition;
					i++;
				}
			}
		}


	}

	// load room data

	std::cout << "ROOMS:" << std::endl;

	int i = 0;

	for (rapidxml::xml_node<> * room = map->first_node("room"); room; room = room -> next_sibling("room")) {
		rooms[i] = new Room();
		rapidxml::xml_node<> * room_name = room->first_node("name");
		rooms[i] -> name = room_name->value();
		rapidxml::xml_node<> * description = room->first_node("description");
		if (description != NULL) {
			rooms[i] -> description = description->value();
		}

		// load items
		int j = 0;
		std::cout << "Items in room: "; 
		for (rapidxml::xml_node<> * item = room->first_node("item"); item; item = item -> next_sibling("item")) {

			
			rooms[i] -> items[j] = item -> value();
			std::cout << rooms[i] -> items[j] <<  " ";
			j++;
		}
		std::cout << '\n';


		// load containers
		j = 0;
		std::cout << "Containers in room: ";
		for (rapidxml::xml_node<> * container = room->first_node("container"); container; container = container->next_sibling("container")) {
			rooms[i]->containers[j] = container->value();
			std::cout << rooms[i]->containers[j] << " ";
			j++;
		}
		std::cout << '\n';


		// load creatures

		j = 0;
		std::cout << "Creatures in room: ";
		for (rapidxml::xml_node<> * creature = room->first_node("creature"); creature; creature = creature->next_sibling("creature")) {
			rooms[i]->creatures[j] = creature->value();
			std::cout << rooms[i]->creatures[j] << " ";
			j++;
		}
		std::cout << '\n';

		// load triggers in room

		int k = 0;
		for (rapidxml::xml_node<> * trigger_node = room->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
			std::cout << "Room triggers..." << std::endl;
			Trigger* trigger = new Trigger();
			int j = 0;

			if (trigger_node->first_node("command")) {
				trigger->command = trigger_node->first_node("command")->value();
				std::cout << "Command: " << trigger->command << std::endl;
			}

			if (trigger_node->first_node("print")) {
				trigger->print = trigger_node->first_node("print")->value();
				std::cout << "Print: " << trigger->print << std::endl;
			}

			// load actions[]

			j = 0;
			std::cout << "Actions: ";
			for (rapidxml::xml_node<> * action_node = room->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
				trigger->action[j] = action_node->value();
				std::cout << trigger->action[j] << " ";
				j++;
			}
			std::cout << '\n';


			// load conditions for room triggers

			j = 0;
			for (rapidxml::xml_node<> * condition_node = trigger_node->first_node("condition"); condition_node; condition_node = condition_node->next_sibling("condition")) {
				Condition* condition = new Condition();
				std::cout << "Conditions for trigger..." << std::endl;
				if (condition_node->first_node("has")) {
					condition->has = condition_node->first_node("has")->value();
					std::cout << "\thas:" << condition->has << std::endl;
				}

				if (condition_node->first_node("object")) {
					condition->object = condition_node->first_node("object")->value();
					std::cout << "\tobject:" << condition->object << std::endl;
				}

				if (condition_node->first_node("owner")) {
					condition->owner = condition_node->first_node("owner")->value();
					std::cout << "\towner:" << condition->owner << std::endl;
				}

				if (condition_node->first_node("status")) {
					condition->status = condition_node->first_node("status")->value();
					std::cout << "\tstatus:" << condition->status << std::endl;
				}

				trigger->conditions[j] = condition;
				j++;

			}

			rooms[i]->triggers[k] = trigger;
			k++;
		}

		// load borders

		j = 0;
		std::cout << "Borders for room: ";
		for (rapidxml::xml_node<> * border = room->first_node("border"); border; border = border->next_sibling("border")) {
			Border* temp = new Border();
			temp->direction = border->first_node("direction")->value();
			temp->room = border->first_node("name")->value();
			rooms[i]->borders[j] = temp;
			std::cout << rooms[i]->borders[j]->room << " to the " << rooms[i]->borders[j]->direction << " ";
			j++;
		}

		std::cout << '\n';

		i++;

	}


	return 0;
}




