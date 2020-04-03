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

    for (unsigned int i = 0; i <= solution.size(); ++i) {
        const std::array<int, 2> &currentPosition
            = m_cities[solution[i%solution.size()]];
        const std::array<int, 2> &nextPosition
            = m_cities[solution[(i+1)%solution.size()]];
        float distance =
            std::sqrt(std::pow(nextPosition[0] - currentPosition[0], 2)
                    + std::pow(nextPosition[1] - currentPosition[1], 2));

        value += m_mapDiagonal - distance;
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
