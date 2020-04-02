#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
T Generate(const G& generator, const E& evaluator, const S& selector, const C& crossOperator, const M& mutationOperator, const A& endCriteria, unsigned int populationSize);

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
inline T Generate(const G & generator, const E & evaluator, const S & selector, const C & crossOperator, M & mutationOperator, const A & endCriteria, unsigned int populationSize)
{
	std::vector<T> populations;
	for(unsigned int i=0; i<populationSize; ++i)
		populations.push_back(generator());

	std::vector<float> notes;
	while (true) {
		for (unsigned int i = 0; i < populations.size(); ++i)
			notes.push_back(evaluator(populations[i]));
		if (endCriteria(notes)) {
			int index = std::distance(notes.begin(), std::max_element(notes.begin(), notes.end()));
			return populations[index];
		}
		else {
			std::vector<T> selections = selector(populations, notes);
			populations.clear();
			notes.clear();
			for (T solution1 : selections) {
				for (T solution2 : selections) {
					if (solution1 == solution2) continue;
					populations.push_back(mutationOperator(crossOperator(solution1, solution2)));
				}
			}
            populations.insert(populations.end(),
                    std::make_move_iterator(selections.begin()),
                    std::make_move_iterator(selections.end()));

            std::cout << "Next gen population:" << std::endl;
            for (T s: populations) {
                std::cout << '{';
                for (unsigned int v: s) {
                    std::cout << v << ' ';
                }
                std::cout << '}' << std::endl;
            }
            std::cout << std::endl;
		}
	}
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
};

template<typename T, typename G, typename E, typename S, typename C, typename M, typename A>
inline GeneticAlgorithm<T, G, E, S, C, M, A>::GeneticAlgorithm(const G& generator, const E& evaluator, const S& selector, const C& crossOperator, M& mutationOperator, const A& endCriteria) : generator(generator), evaluator(evaluator), selector(selector), crossOperator(crossOperator), mutationOperator(mutationOperator), endCriteria(endCriteria)
{}

template <typename T, typename G, typename E, typename S, typename C, typename M, typename A>
T GeneticAlgorithm<T, G, E, S, C, M, A>::Run(unsigned int populationSize)
{
	return Generate< T, G, E, S, C, M, A>(generator, evaluator, selector, crossOperator, mutationOperator, endCriteria, populationSize);
}
