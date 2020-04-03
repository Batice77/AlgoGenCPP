#include <random>
#include <iostream>

#include "TravelingSalesmanProblemEvaluator.h"

TravelingSalesmanProblemEvaluator::TravelingSalesmanProblemEvaluator(unsigned int citiesToGenerate, unsigned int mapWidth, unsigned int mapHeight) :
    m_citiesToGenerate(citiesToGenerate),
    m_mapWidth(mapWidth),
    m_mapHeight(mapHeight)
{
    m_mapDiagonal = std::sqrt(std::pow(m_mapWidth, 2)
            + std::pow(mapHeight, 2));
}

void TravelingSalesmanProblemEvaluator::init()
{
    std::random_device rd;
    std::mt19937 g(rd());
	std::uniform_int_distribution<> distributionWidth
        = std::uniform_int_distribution<>(0, m_mapWidth);
	std::uniform_int_distribution<> distributionHeight
        = std::uniform_int_distribution<>(0, m_mapHeight);

    for (unsigned int i = 0; i < m_citiesToGenerate; ++i) {
        std::array<int, 2> city = {distributionWidth(g), distributionHeight(g)};
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
