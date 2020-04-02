#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

#include "TravelingSalesmanProblemGenerator.h"

TravelingSalesmanProblemGenerator::TravelingSalesmanProblemGenerator(unsigned int citiesCount) :
    m_citiesCount(citiesCount)
{}

std::vector<unsigned int> TravelingSalesmanProblemGenerator::operator()() const
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<unsigned int> population(m_citiesCount);
    std::iota (std::begin(population), std::end(population), 0);
    std::shuffle (std::begin(population), std::end(population), g);

    return population;
}
