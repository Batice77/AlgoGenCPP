#pragma once

#include <vector>

class TravelingSalesmanProblemGenerator
{
    public:
        TravelingSalesmanProblemGenerator(unsigned int citiesCount);
        std::vector<unsigned int> operator()() const;

    private:
        unsigned int m_citiesCount;
};
