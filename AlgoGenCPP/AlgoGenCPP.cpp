// AlgoGenCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>

int main()
{
    std::cout << "Welcome to PlanetSim, the life simulator of entities (ALPHA)\n";
	bool toExit = false;

	//TODO DECLARE EVOLVING VARS
	int gen = 0;
	int maxgen = 0;
	std::cout << "Please enter how many generation you want : ";
	std::cin >> maxgen;

	while (!toExit) {
		//TODO EVOLVING
		gen++;


		//Checkers
		if (gen >= maxgen) {
			toExit = true;
		}
	}
	
	//Clear CIN
	std::string dummy;
	std::getline(std::cin, dummy);

	std::cout << "We made " << gen << " generations";
	std::cin.get();
	return 0;
}