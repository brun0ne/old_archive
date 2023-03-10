#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "main.h"

int main(){ // MENU

	// for debug ->

	//game(); return 0;

	// <-

	int input;

	std::cout << "Project1\n" << "1. Play\n" << "2. Play on last world seed.\n" << "3. Enter world seed.\n" << "4. Exit\n\n" << "Type 1/2/3\n\n";

	std::cin >> input;

	std::ifstream seedFile;
	std::string seed;

	switch (input)
	{
	case 1:
		game(0); // game

		break;

	case 2:
		seedFile.open("lastseed.txt");

		if (seedFile) {
			seedFile >> seed;
		}

		game(std::stoi(seed));

		break;

	case 3:
		int cinseed;

		std::cin >> cinseed;

		game(cinseed);

		break;

	case 4:
		break; // exit
	}

    return 0;
}