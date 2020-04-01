#pragma once
#include <vector>

class SumsThreshold
{
public:
	SumsThreshold()
	{
	}
	~SumsThreshold() {};

	bool operator()(const std::vector<float> qualityList) {
		return false;
	}
};

