#pragma once
#include <vector>

class QualityThreshold
{
public:
	QualityThreshold(float qualityValue) : qualityThreshold(qualityValue) {}
	~QualityThreshold(){};

	bool operator()(const std::vector<float> qualityList) const {
		for (int i = 0; i < qualityList.size(); i++) {
			if (qualityList[i] >= qualityThreshold) {
				return true;
			}
		}
		return false;
	}

private:
	float qualityThreshold;
};

