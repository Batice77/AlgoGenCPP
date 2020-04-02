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

class Selector;
class CrossOperator;
class MutationOperator;
class EndCriteria;

int main()
{
    std::cout << "Begin tests" << std::endl;

    std::cout << "Instanciate all GeneticAlgorithm parameters" << std::endl;

    unsigned int citiesToGenerate = 10;
    unsigned int populationSize = 100;
    unsigned int populationKept = 60;

    TravelingSalesmanProblemEvaluator evaluator(citiesToGenerate);
    const TravelingSalesmanProblemGenerator generator(citiesToGenerate);
    const ElitismSelector<std::vector<unsigned int>> selector(populationKept);
    const VoyagerCrossOperator crossOperator;
    TravelerMutator mutationOperator(citiesToGenerate, 0.15f);
    const QualityThreshold qualityThreshold(1300);

    evaluator.init();

    std::cout << "Instanciate GeneticAlgorithm" << std::endl;

    GeneticAlgorithm<std::vector<unsigned int>,
        TravelingSalesmanProblemGenerator, TravelingSalesmanProblemEvaluator,
        ElitismSelector<std::vector<unsigned int>>, VoyagerCrossOperator,
        TravelerMutator, QualityThreshold>
            geneticAlgorithm (generator, evaluator,
                selector, crossOperator, mutationOperator, qualityThreshold);

    std::vector<unsigned int> result = geneticAlgorithm.Run(populationSize);

    std::cout << "The result is: {";
    for (unsigned int v: result) {
        std::cout << v << ' ';
    }
    std::cout << "}" << std::endl;

    std::vector<std::array<int, 2>> cities = evaluator.getCities();

    std::cout << "Cities traveled:" << std::endl;
    for (unsigned int v: result) {
        std::cout << cities[v][0] << ' ' << cities[v][1] << std::endl;
    }
}
