#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>

#include "TravelingSalesmanProblemGenerator.h"

TravelingSalesmanProblemGenerator::TravelingSalesmanProblemGenerator(unsigned int citiesCount) :
    m_citiesCount(citiesCount)
{}

std::vector<unsigned int> TravelingSalesmanProblemGenerator::operator()() const
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<unsigned int> solution(m_citiesCount);
    std::iota (std::begin(solution), std::end(solution), 0);
    std::shuffle (std::begin(solution), std::end(solution), g);

    std::cout << "Generated solution: {";
    for (unsigned int v: solution) {
        std::cout << v << ' ';
    }
    std::cout << "}" << std::endl;

    return solution;
}
