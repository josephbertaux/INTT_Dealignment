#ifndef TAIT_BRYAN_ZYX_H
#define TAIT_BRYAN_ZYX_H

#include "AngleConvention.h"

class TaitBryanZYX: public AngleConvention
{
	std::map<std::string, int> indexes;
public:
	TaitBryanZYX();
	int SetTransformFromAngles(std::array<std::array<double, 4>, 4>&, std::array<double, 3> const&) override;
	int SetAnglesFromTransform(std::array<std::array<double, 4>, 4> const&, std::array<double, 3>&) override;
	int GetAngle(std::string const&) override;
};

#endif
