#pragma once
#include <vector>

template <typename T>
class VoyagerCrossOperator 
{
public :
	VoyagerCrossOperator() {};
	VoyagerCrossOperator() {};

	std::vector<T> operator()(std::vector<T> list1, std::vector<T> list2) {
		std::vector<T> res;

		int lim1 = list1.size() / 2;
		int lim2 = list2.size() / 2;

		for (int i = 0; i <= lim1; i++) {
			res.push_back(list1[i]);
		}
		for (int i = 0; i < lim2; i++) {
			res.push_back(list2[list2.size() - lim2 + i);
		}
		return res;
	}
};