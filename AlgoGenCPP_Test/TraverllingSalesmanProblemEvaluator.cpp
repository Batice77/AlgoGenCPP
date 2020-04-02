#include <cmath>
#include <set>
#include <random>

#include "TraverllingSalesmanProblemEvaluator.h"

TravelingSalesmanProblemEvaluator::TravelingSalesmanProblemEvaluator(unsigned int citiesToGenerate, float alreadyVisitedMalus = 141.421356237, unsigned int mapWidth = 100, unsigned int mapHeight = 100) :
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

template<class T>
float TravelingSalesmanProblemEvaluator::evaluate(const T& solution) const
{
    float value = 0;

    std::array<int, 2> currentPosition;
    std::set<std::array<int, 2>> visitedCities;

    for (int i = 0; i < solution.size(); ++i) {
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

template<class T>
float TravelingSalesmanProblemEvaluator::operator()(const T& solution) const
{
    return evaluate(solution);
}