#pragma once

#include <vector>

class TravelingSalesmanProblemMutator
{
    public:
        std::vector<unsigned int> operator()(std::vector<unsigned int> solution)
            const
        {
            return solution;
        }
};
