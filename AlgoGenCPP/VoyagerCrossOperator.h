#pragma once
#include <vector>
#include <algorithm>

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

		std::vector<unsigned int> values = list2;
		std::vector<unsigned int> verif;
		for (int i = 0; i < res.size(); i++) {
			while(std::find(verif.begin(),verif.end(),values[values.size()]) != verif.end())
			{
				//tant qu'on a une value deja presente
				values.pop_back();
			}

			if (std::find(verif.begin(), verif.end(), res[i]) != verif.end())
			{
				//ELEMENT FOUND
				res[i] = values[values.size()];
			}
			else
			{
				verif.push_back(res[i]);
			}
		}
		return res;
	}
};
