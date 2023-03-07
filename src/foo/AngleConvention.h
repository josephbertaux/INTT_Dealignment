#ifndef ANGLE_CONVENTION_H
#define ANGLE_CONVENTION_H

#include <map>
#include <array>
#include <string>
#include <cstring>
#include <math.h>
#include <iostream>

class AngleConvention
{
public:
	virtual int SetTransformFromAngles(std::array<std::array<double, 4>, 4>&, std::array<double, 3> const&);
	virtual int SetAnglesFromTransform(std::array<std::array<double, 4>, 4> const&, std::array<double, 3>&);
	virtual int GetAngle(std::string const&);
};

#endif
