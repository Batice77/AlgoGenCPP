#pragma once
#include <vector>
#include <random>

class TravelerMutator {
	int nbVille;
	float probability;
	std::default_random_engine generator;
	std::uniform_real_distribution<> distributionProba;
	std::uniform_int_distribution<> distributionVille;

public:
	TravelerMutator(int nbVille, float probability) : nbVille(nbVille), probability(probability)
	{
		distributionVille = std::uniform_int_distribution<>(0, nbVille-1);
	}

	std::vector<unsigned int> operator()(std::vector<unsigned int> solution)
	{
		if (distributionProba(generator) <= probability) {
			int indexVille = distributionVille(generator);
			int indexSequence = std::uniform_int_distribution<>(0, solution.size()-1)(generator);
			solution[indexSequence] = indexVille;
		}

		return solution;
	}
};