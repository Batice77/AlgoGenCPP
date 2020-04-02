#pragma once
#include <vector>

class VoyagerCrossOperator
{
public :
	VoyagerCrossOperator() {};

	std::vector<unsigned int> operator()(std::vector<unsigned int> list1, std::vector<unsigned int> list2) const {
		std::vector<unsigned int> res;

		int lim1 = list1.size() / 2;

		for (int i = 0; i < lim1; i++) {
			res.push_back(list1[i]);
		}
		for (unsigned int i = lim1; i < list2.size(); i++) {
			res.push_back(list2[i]);
		}
		return res;
	}
};
