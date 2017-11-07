#include "Base.h"
#ifndef CREATURE_H_
#define CREATURE_H_

class Creature : public Base {
public:
	std::vector<std::string> vulnerabilities;
	Trigger* attack;

	Creature(rapidxml::xml_node<>*);
	~Creature();

};

#endif