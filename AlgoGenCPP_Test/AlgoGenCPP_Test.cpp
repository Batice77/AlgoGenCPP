#include <iostream>
#include <string>
#include <cstdlib>

#include "../AlgoGenCPP/GeneticAlgorithm.h"
#include "../AlgoGenCPP/QualityThreshold.h"
#include "../AlgoGenCPP/ElitismSelector.h"
#include "../AlgoGenCPP/VoyagerCrossOperator.h"
#include "../AlgoGenCPP/TravelerMutator.h"
#include "TravelingSalesmanProblemEvaluator.h"
#include "TravelingSalesmanProblemGenerator.h"
#include "TravelingSalesmanProblemMutator.h"
#include "Scene.h"

class Selector;
class CrossOperator;
class MutationOperator;
class EndCriteria;

// Main code
int main(int, char**)
{
	//Creation de la scene
	Scene scene("Chapitre 3", 800, 600);
	//Initialisation de la scene
	if (scene.initialiserFenetre() == false)
		return -1;

	if (scene.initGL() == false)
		return -1;
	
	if (scene.initImGui() == false)
		return -1;

	//Boucle Principale
	scene.bouclePrincipale();

	std::cout << "test" << std::endl;

	return 0;
}