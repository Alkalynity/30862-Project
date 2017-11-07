// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <fstream>
#include <sstream>
#include "Base.h"
#include "Item.h"
#include "Map.h"


int main(int argc, char* argv[]) {
	Map * game = new Map("xml_test.xml");
	game -> printItems();
	game->printContainers();
	game->printCreatures();
	game->printRooms();
    return 0;
}

