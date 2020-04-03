#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <iterator>

class VoyagerCrossOperator
{
public :
	VoyagerCrossOperator() {};

	std::vector<unsigned int> operator()(std::vector<unsigned int> list1, std::vector<unsigned int> list2) const {
		std::vector<unsigned int> res;
		unsigned int lim1 = list1.size() / 2;

		for (unsigned int i = 0; i < lim1; i++) {
			res.push_back(list1[i]);
		}
		for (unsigned int i = lim1; i < list2.size(); i++) {
			res.push_back(list2[i]);
		}

        std::random_device rd;
        std::mt19937 g(rd());
        std::vector<unsigned int> values(list1.size());
        std::iota (std::begin(values), std::end(values), 0);
        std::set<unsigned int> possibleValues(values.begin(), values.end());

		std::set<unsigned int> containedInRes(res.begin(), res.end());
		std::set<unsigned int> notInRes;
        std::set_difference(possibleValues.begin(), possibleValues.end(),
                containedInRes.begin(), containedInRes.end(),
                std::inserter(notInRes, notInRes.begin()));

		std::set<unsigned int> encountered;

		for (unsigned int i = 0; i < res.size(); i++) {
            if (std::count(encountered.begin(), encountered.end(),
                        res[i]) != 0) {
                res[i] = *(notInRes.begin());
                notInRes.erase(notInRes.begin());
            }
            encountered.emplace(res[i]);
		}

        return res;
	}
};
