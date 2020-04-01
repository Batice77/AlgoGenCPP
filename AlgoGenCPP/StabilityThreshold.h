#pragma once
#include <vector>

class StabilityThreshold
{
public:
	StabilityThreshold(int stableThreshold) : stable_th(stableThreshold)
	{
		stable_it = 0;
	}
	~StabilityThreshold() {};

	bool operator()(const std::vector<float> qualityList) {
		if (last_val.size == 0) {
			last_val = qualityList;
			return false;
		}

		if (qualityList == last_val) {
			stable_it++;
			return stable_it >= stable_th;
		}
		else
		{
			stable_it = 0;
			last_val = qualityList;
			return false;
		}
	}

private:
	int stable_it;
	int stable_th;
	std::vector<float> last_val;
};

