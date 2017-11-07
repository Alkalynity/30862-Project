#include "Condition.h"
#ifndef TRIGGER_H_
#define TRIGGER_H_

class Trigger {
public:
	std::string command; // make this vector<> of commands? I don't know if we need to consider multiple commands
	std::vector<std::string> print;
	std::vector<std::string> action;
	std::string type;
	std::vector<Condition*> conditions;

	Trigger(rapidxml::xml_node<>*);
	~Trigger();
};

#endif
