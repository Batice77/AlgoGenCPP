#pragma once

#include <list>
#include <array>

class TravelingSalesmanProblemEvaluator
{
    public:
        TravelingSalesmanProblemEvaluator(unsigned int citiesToGenerate,
                float alreadyVisitedMalus, unsigned int mapWidth,
                unsigned int mapHeight);
        void init();
        template<class T> float evaluate(const T& solution) const;
        template<class T> float operator()(const T& solution) const;

    private:
        unsigned int m_citiesToGenerate;
        float m_alreadyVisitedMalus;
        unsigned int m_mapWidth;
        unsigned int m_mapHeight;
        unsigned int m_mapDiagonal;
        std::list<std::array<int, 2>> m_cities;
};
