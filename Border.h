#include "Base.h"
#ifndef BORDER_H_
#define BORDER_H_

class Border : public Base {
public:
	Border(rapidxml::xml_node<>*);
	~Border();
	std::string room;
	std::string direction;
};

#endif