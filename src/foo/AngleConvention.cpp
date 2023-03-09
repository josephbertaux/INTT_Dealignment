#include "AngleConvention.h"

AngleConvention::AngleConvention()
{
	indexes["x"] = 0;
	indexes["y"] = 1;
	indexes["z"] = 2;
}

int AngleConvention::SetTransformFromAngles(std::array<std::array<double, 4>, 4>&, std::array<double, 3> const&)
{
	return 1;
}

int AngleConvention::SetAnglesFromTransform(std::array<std::array<double, 4>, 4> const&, std::array<double, 3>&)
{
	return 1;
}

int AngleConvention::GetAngle(std::string const& s)
{
	if(indexes.find(s) == indexes.end())
	{
		return -1;
	}

	return indexes[s];
}
