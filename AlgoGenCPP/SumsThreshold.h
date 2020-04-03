#pragma once
#include <vector>

template <typename T, typename I, typename Q, typename S>
class SumsThreshold
{
public:
	SumsThreshold(I& it, const Q& qual, S& stab);
	~SumsThreshold() {};

	bool operator()(const std::vector<float> qualityList) const {
		return iterative(qualityList) || quality(qualityList) || stability(qualityList);
	}

protected:
	I& iterative;
	const Q& quality;
	S& stability;
};

template<typename T, typename I, typename Q, typename S >
inline SumsThreshold<T, I, Q, S>::SumsThreshold(I& it, const Q& qual, S& stab):iterative(it), quality(qual), stability(stab) {}

