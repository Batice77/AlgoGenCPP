#include "BreakPoint.h"

BreakPoint::BreakPoint(int maxIt, float nt, int maxfreeze)
{
	cur_it = 0;
	last_it_mod = 0;

	th_it = maxIt;
	th_nt = nt;
	max_plat = maxfreeze;
}

BreakPoint::~BreakPoint()
{
}

bool BreakPoint::QualityThresh()
{
	float qual = -99.9;

	//Loop element
		if(qual >= th_nt)//The solution is good enough
			return true;//Exit
	//end loop

	return false;
}

bool BreakPoint::IteThresh()
{
	return cur_it >= th_it;
}

bool BreakPoint::StabilityThresh()
{
	return (cur_it - last_it_mod) >= max_plat;
}

bool BreakPoint::Thresh()
{
	return QualityThresh() || IteThresh() || StabilityThresh();
}

bool BreakPoint::UpdateThresh()
{
	cur_it++;

	//If has changed
	last_it_mod = cur_it;

	return Thresh();
}
