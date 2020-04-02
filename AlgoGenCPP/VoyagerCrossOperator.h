#pragma once
#include <vector>

class VoyagerCrossOperator
{
public :
	VoyagerCrossOperator() {};

	std::vector<unsigned int> operator()(std::vector<unsigned int> list1, std::vector<unsigned int> list2) const {
		std::vector<unsigned int> res;

		int lim1 = list1.size() / 2;
		int lim2 = list2.size() / 2;

		for (int i = 0; i <= lim1; i++) {
			res.push_back(list1[i]);
		}
		for (int i = 0; i < lim2; i++) {
			res.push_back(list2[list2.size() - lim2 + i]);
		}
		return res;
	}
};
