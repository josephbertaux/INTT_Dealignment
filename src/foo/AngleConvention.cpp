#include "AngleConvention.h"

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
	if(strcmp(s.c_str(), "x") == 0)return 0;
	if(strcmp(s.c_str(), "y") == 0)return 1;
	if(strcmp(s.c_str(), "z") == 0)return 2;

	return -1;
}
