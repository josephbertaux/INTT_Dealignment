#ifndef INTT_PARAMETERS_H
#define INTT_PARAMETERS_H

#include <cmath>

namespace INTT
{
	const double PI = atan(1.0) * 4;

	constexpr int LAYER=		4;
	constexpr int LADDER[4]=	{12,		12,		16,		16};
	constexpr int SENSOR=		4;
	constexpr int STRIP_X[4]=	{5,		8,		8,		5};
	constexpr int STRIP_Y=		256;

	constexpr double RADIUS[4]=	{7.187489,	7.799527,	9.880091,	10.328663};
	constexpr double PHI_M[4]=	{PI / 6.0,	PI / 6.0,	PI / 8.0,	PI / 8.0};
	constexpr double PHI_B[4]=	{PI / 12.0,	0.0,		PI / 16.0,	0.0};
	constexpr double SENSOR_X[4]=	{-181.75,	-65.55,		65.55,		65.55};

	//crude but close
	constexpr double STRIP_XM[4]=	{20.3,		16.1875,	16.1875,	20.3};
	constexpr double STRIP_XB[4]=	{-222.35,	-122.20625,	8.89375,	141.15};

	constexpr double STRIP_YM=	0.0859375;
	constexpr double STRIP_YB=	-10.95703125;
};

#endif
