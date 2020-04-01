#pragma once
#include <vector>

class IterativeThreshold
{
public:
	IterativeThreshold(int maxit):max_it(maxit)
	{
		cur_it = 0;
	}
	~IterativeThreshold() {};

	bool operator()(const std::vector<float> qualityList) {
		cur_it++;
		return cur_it >= max_it;
	}

private:
	int cur_it;
	int max_it;
};

