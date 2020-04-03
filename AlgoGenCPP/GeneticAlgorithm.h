#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
T Generate(const G& generator, const E& evaluator, const S& selector, const C& crossOperator, const M& mutationOperator, const A& endCriteria, unsigned int populationSize);

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
bool Step(std::vector<T> & populations, std::vector<float> & notes, T & bestSolution, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria);

template <typename T, typename G>
std::vector<T> Init(const G& generator, unsigned int populationSize)
{
    std::vector<T> populations;

    for(unsigned int i=0; i<populationSize; ++i) {
        populations.push_back(generator());
    }

    return populations;
}

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
bool Step(std::vector<T> & populations, std::vector<float> & notes, T & bestSolution, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria)
{
    for (unsigned int i = 0; i < populations.size(); ++i) {
        notes.push_back(evaluator(populations[i]));
    }

    //std::cout << "Evaluated population:" << std::endl;
    //for (unsigned int i = 0; i < populations.size(); ++i) {
    //    std::cout << '{';
    //    for (unsigned int v: populations[i]) {
    //        std::cout << v << ' ';
    //    }
    //    std::cout << "} value: " << notes[i] <<  std::endl;
    //}
    //std::cout << std::endl;

    int index = std::distance(notes.begin(), std::max_element(notes.begin(), notes.end()));
    bestSolution = populations[index];

    if (endCriteria(notes)) {
        return true;
    }
    else {
        std::vector<T> selections = selector(populations, notes);
        populations.clear();
        notes.clear();
        for (unsigned int i = 0; i < selections.size(); ++i) {
            for (unsigned int j = 0; j < selections.size(); ++j) {
                if (i == j) continue;
                populations.push_back(mutationOperator(crossOperator(selections[i], selections[j])));
            }
        }
        populations.insert(populations.end(),
                std::make_move_iterator(selections.begin()),
                std::make_move_iterator(selections.end()));
        return false;
    }
}

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
inline T Generate(const G & generator, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria, unsigned int populationSize)
{
	std::vector<T> populations = Init<T, G>(generator, populationSize);
	std::vector<float> notes;
    T bestSolution;

	while (!Step<T, G, E, S, C, M, A>(populations, notes, bestSolution, evaluator, selector, crossOperator, mutationOperator, endCriteria)) {}

    return bestSolution;
}

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
class GeneticAlgorithm
{
protected:
	const G& generator;
	const E& evaluator;
	const S& selector;
	const C& crossOperator;
	M& mutationOperator;
	const A& endCriteria;

public:
	GeneticAlgorithm(const G& generator, const E& evaluator, const S& selector, const C& crossOperator, M& mutationOperator, const A& endCriteria);
	T Run(unsigned int populationSize);
    std::vector<T> Init(const G& generator, unsigned int populationSize);
    bool Step(std::vector<T> & populations, std::vector<float> & notes, T & bestSolution, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria);
};

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
inline GeneticAlgorithm<T, G, E, S, C, M, A>::GeneticAlgorithm(const G& generator, const E& evaluator, const S& selector, const C& crossOperator, M& mutationOperator, const A& endCriteria) : generator(generator), evaluator(evaluator), selector(selector), crossOperator(crossOperator), mutationOperator(mutationOperator), endCriteria(endCriteria)
{}

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
T GeneticAlgorithm<T, G, E, S, C, M, A>::Run(unsigned int populationSize)
{
	return Generate< T, G, E, S, C, M, A>(generator, evaluator, selector, crossOperator, mutationOperator, endCriteria, populationSize);
}

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
bool GeneticAlgorithm<T, G, E, S, C, M, A>::Step(std::vector<T> & populations, std::vector<float> & notes, T & bestSolution, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria)
{
    return ::Step<T, G, E, S, C, M, A>(populations, notes, bestSolution, evaluator, selector, crossOperator, mutationOperator, endCriteria);
}

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
std::vector<T> GeneticAlgorithm<T, G, E, S, C, M, A>::Init(const G& generator, unsigned int populationSize)
{
    return ::Init<T>(generator, populationSize);
}
