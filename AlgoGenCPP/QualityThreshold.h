#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

class QualityThreshold
{
public:
	QualityThreshold(float qualityValue) : qualityThreshold(qualityValue) {}
	~QualityThreshold(){};

	bool operator()(const std::vector<float> qualityList) const {
		for (unsigned int i = 0; i < qualityList.size(); i++) {
			if (qualityList[i] >= qualityThreshold) {
                std::cout << "Max value: " << *std::max_element(qualityList.begin(), qualityList.end()) << std::endl;
				return true;
			}
		}

        std::cout << "Average value: " << std::accumulate(qualityList.begin(), qualityList.end(), 0.f) / qualityList.size() << std::endl;

		return false;
	}

private:
	float qualityThreshold;
};

