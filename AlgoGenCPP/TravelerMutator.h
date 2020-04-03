#pragma once
#include <vector>
#include <random>

class TravelerMutator {
	int nbVille;
	float probability;
	std::uniform_real_distribution<> distributionProba;
	std::uniform_int_distribution<> distributionVille;

public:
	TravelerMutator(int nbVille, float probability) : nbVille(nbVille), probability(probability)
	{
		distributionVille = std::uniform_int_distribution<>(0, nbVille-1);
	}

	std::vector<unsigned int> operator()(std::vector<unsigned int> solution) const
	{
		std::random_device random_device;
		std::mt19937 engine{ random_device() };
		if (distributionProba(engine) <= probability) {
			int indexSequence1 = distributionVille(engine);
			int indexSequence2 = distributionVille(engine);
			std::swap(solution[indexSequence1], solution[indexSequence2]);
		}

		return solution;
	}
};