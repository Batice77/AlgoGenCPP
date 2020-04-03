#include <iostream>
#include <string>
#include <cstdlib>

#include "../AlgoGenCPP/GeneticAlgorithm.h"
#include "../AlgoGenCPP/QualityThreshold.h"
#include "../AlgoGenCPP/IterativeThreshold.h"
#include "../AlgoGenCPP/StabilityThreshold.h"
#include "../AlgoGenCPP/SumsThreshold.h"
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
    float valueThreshold = citiesToGenerate * citiesToGenerate * 13;
    unsigned int maxIterations = 20;
    unsigned int stableIterations = 5;

    TravelingSalesmanProblemEvaluator evaluator(citiesToGenerate);
    const TravelingSalesmanProblemGenerator generator(citiesToGenerate);
    const ElitismSelector<std::vector<unsigned int>> selector(populationKept);
    const VoyagerCrossOperator crossOperator;
    TravelerMutator mutationOperator(citiesToGenerate, 0.15f);
    const QualityThreshold qualityThreshold(valueThreshold);
    IterativeThreshold iterativeThreshold(maxIterations);
    StabilityThreshold stabilityThreshold(stableIterations);
    const SumsThreshold<std::vector<unsigned int>, IterativeThreshold,
          QualityThreshold, StabilityThreshold>
              sumsThreshold(iterativeThreshold, qualityThreshold,
                      stabilityThreshold);

    evaluator.init();

    std::cout << "Instanciate GeneticAlgorithm" << std::endl;

    GeneticAlgorithm<std::vector<unsigned int>,
        TravelingSalesmanProblemGenerator, TravelingSalesmanProblemEvaluator,
        ElitismSelector<std::vector<unsigned int>>, VoyagerCrossOperator,
        TravelerMutator, SumsThreshold<std::vector<unsigned int>,
        IterativeThreshold, QualityThreshold, StabilityThreshold>>
            geneticAlgorithm (generator, evaluator,
                selector, crossOperator, mutationOperator, sumsThreshold);

    std::vector<std::vector<unsigned int>> populations
        = geneticAlgorithm.Init(generator, populationSize);
    std::vector<float> notes;
    std::vector<unsigned int> bestSolution;
    while (!geneticAlgorithm.Step(populations, notes, bestSolution, evaluator, selector, crossOperator, mutationOperator, sumsThreshold)) {
        std::cout << "Best solution: {";
        for (unsigned int v: bestSolution) {
            std::cout << v << ' ';
        }
        std::cout << "}" << std::endl;
    }

    //std::vector<unsigned int> result = geneticAlgorithm.Run(populationSize);

    //std::cout << "The result is: {";
    //for (unsigned int v: result) {
    //    std::cout << v << ' ';
    //}
    //std::cout << "}" << std::endl;

    std::vector<std::array<int, 2>> cities = evaluator.getCities();

    std::cout << "Cities traveled:" << std::endl;
    for (unsigned int v: bestSolution /*result*/) {
        std::cout << cities[v][0] << ' ' << cities[v][1] << std::endl;
    }
}
