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
#include <crtdbg.h>


int main(int argc, char* argv[]) {
	std::string input;
	std::cout << "Input file name: ";
	std::getline(std::cin, input);

	Map * game = new Map(input);
	game->run();
	/*
	game -> printItems();
	game->printContainers();
	game->printCreatures();
	game->printRooms();
	*/
	//_CrtDumpMemoryLeaks();
	return 0;
}

