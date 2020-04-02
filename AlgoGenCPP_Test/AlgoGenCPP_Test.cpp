#include <iostream>
#include <string>
#include <cstdlib>

#include "../AlgoGenCPP/GeneticAlgorithm.h"
#include "../AlgoGenCPP/QualityThreshold.h"
#include "../AlgoGenCPP/ElitismSelector.h"
#include "../AlgoGenCPP/VoyagerCrossOperator.h"
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

    const TravelingSalesmanProblemEvaluator evaluator(citiesToGenerate);
    const TravelingSalesmanProblemGenerator generator(citiesToGenerate);
    const ElitismSelector<std::vector<unsigned int>> selector(populationKept);
    const VoyagerCrossOperator crossOperator;
    const TravelingSalesmanProblemMutator mutationOperator;
    const QualityThreshold qualityThreshold(1);

    std::cout << "Instanciate GeneticAlgorithm" << std::endl;

    GeneticAlgorithm<std::vector<unsigned int>,
        TravelingSalesmanProblemGenerator, TravelingSalesmanProblemEvaluator,
        ElitismSelector<std::vector<unsigned int>>, VoyagerCrossOperator,
        TravelingSalesmanProblemMutator, QualityThreshold>
            geneticAlgorithm (generator, evaluator,
                selector, crossOperator, mutationOperator, qualityThreshold);

    std::vector<unsigned int> result = geneticAlgorithm.Run(populationSize);
}
