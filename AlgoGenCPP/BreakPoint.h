#pragma once

class BreakPoint
{
public:
	BreakPoint(int maxIt, float nt, int maxfreeze);
	~BreakPoint();

	bool QualityThresh();
	bool IteThresh();
	bool StabilityThresh();
	bool Thresh();

	bool UpdateThresh();

private:
	int cur_it;
	int last_it_mod;

	int th_it;
	float th_nt;
	int max_plat;
};

