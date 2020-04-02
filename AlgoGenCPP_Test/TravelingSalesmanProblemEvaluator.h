#pragma once

#include <vector>
#include <array>

class TravelingSalesmanProblemEvaluator
{
    public:
        TravelingSalesmanProblemEvaluator(unsigned int citiesToGenerate,
                float alreadyVisitedMalus = 141.421356237,
                unsigned int mapWidth = 100, unsigned int mapHeight = 100);
        void init();
        float evaluate(const std::vector<unsigned int>& solution) const;
        float operator()(const std::vector<unsigned int>& solution) const;
        std::vector<std::array<int, 2>> getCities() const;

    private:
        unsigned int m_citiesToGenerate;
        float m_alreadyVisitedMalus;
        unsigned int m_mapWidth;
        unsigned int m_mapHeight;
        unsigned int m_mapDiagonal;
        std::vector<std::array<int, 2>> m_cities;
};
