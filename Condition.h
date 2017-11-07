#include <iostream>
#ifndef CONDITION_H_
#define CONDITION_H_
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

class Condition {
public:
	std::string has;
	std::string object;
	std::string owner;
	std::string status;

	Condition(rapidxml::xml_node<>*);
	~Condition();

};
#endif