#include <set>
#include <random>
#include <iostream>

#include "TravelingSalesmanProblemEvaluator.h"

TravelingSalesmanProblemEvaluator::TravelingSalesmanProblemEvaluator(unsigned int citiesToGenerate, float alreadyVisitedMalus, unsigned int mapWidth, unsigned int mapHeight) :
    m_citiesToGenerate(citiesToGenerate),
    m_alreadyVisitedMalus(alreadyVisitedMalus),
    m_mapWidth(mapWidth),
    m_mapHeight(mapHeight)
{
    m_mapDiagonal = std::sqrt(std::pow(m_mapWidth, 2)
            + std::pow(mapHeight, 2));
}

void TravelingSalesmanProblemEvaluator::init()
{
    std::minstd_rand rand;

    for (unsigned int i = 0; i < m_citiesToGenerate; ++i) {
        std::array<int, 2> city =
        {static_cast<int>(rand()/((rand.max() + 1u)/m_mapWidth)),
            static_cast<int>(rand()/((rand.max() + 1u)/m_mapHeight))};
        m_cities.push_back(city);
    }
}

float TravelingSalesmanProblemEvaluator::evaluate(const std::vector<unsigned int>& solution) const
{
    float value = 0;

    std::array<int, 2> currentPosition = m_cities[solution[0]];
    std::set<std::array<int, 2>> visitedCities;

    for (unsigned int i = 1; i < solution.size(); ++i) {
        std::array<int, 2> nextPosition = m_cities[solution[i]];
        float distance =
            std::sqrt(std::pow(nextPosition[0] - currentPosition[0], 2)
                    + std::pow(nextPosition[0] - currentPosition[0], 2));

        if (visitedCities.count(nextPosition) != 0) {
            value -= m_alreadyVisitedMalus;
        }

        value += m_mapDiagonal - distance;

        currentPosition = nextPosition;
    }

    return value;
}

float TravelingSalesmanProblemEvaluator::operator()(const std::vector<unsigned int>& solution) const
{
    return evaluate(solution);
}

std::vector<std::array<int, 2>> TravelingSalesmanProblemEvaluator::getCities()
    const
{
    return m_cities;
}
