#pragma once
#include <vector>

template <typename T, typename I, typename Q, typename S>
class SumsThreshold
{
public:
	SumsThreshold(const I& it, const Q& qual, const S& stab);
	~SumsThreshold() {};

	bool operator()(const std::vector<float> qualityList) {
		return iterative(qualityList) || quality(qualityList) || stability(qualityList);
	}

protected:
	const I& iterative;
	const Q& quality;
	const S& stability;
};

template<typename T, typename I, typename Q, typename S >
inline SumsThreshold<T, I, Q, S>::SumsThreshold(const I& it, const Q& qual, const S& stab):iterative(it), quality(qual), stability(stab) {};

