/*
 * Base.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: jcbar
 */
#include"Base.h"

Base::Base() {
}

Base::~Base() {

}

Trigger* Base::checkTriggers(std::string command) {
	for (std::vector<Trigger*>::iterator q = triggers.begin(); q != triggers.end(); ++q) {
		if ((*q)->command == command) {
			return (*q);
		}
	}
	return NULL;
}
