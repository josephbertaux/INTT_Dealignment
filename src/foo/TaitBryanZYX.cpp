#include "TaitBryanZYX.h"

int TaitBryanZYX::SetTransformFromAngles(std::array<std::array<double, 4>, 4>& t, std::array<double, 3> const& a)
{
	double s_0 = sin(a[0]);	double c_0 = cos(a[0]);
	double s_1 = sin(a[1]);	double c_1 = cos(a[1]);
	double s_2 = sin(a[2]);	double c_2 = cos(a[2]);

	t[0][0] = c_0 * c_1;	t[0][1] = c_0 * s_1 * s_2 - c_2 * s_0;	t[0][2] = s_0 * s_2 + c_0 * c_2 * s_1;
	t[1][0] = c_1 * s_0;	t[1][1] = c_0 * c_2 + s_0 * s_1 * s_2;	t[1][2] = c_2 * s_0 * s_1 - c_0 * s_2;
	t[2][0] = -s_1;		t[2][1] = c_1 * s_2;			t[2][2] = c_1 * c_2;
	t[3][0] = 0.0;		t[3][1] = 0.0;				t[3][2] = 0.0;				t[3][3] = 1.0;
	
	return 0;
}

int TaitBryanZYX::SetAnglesFromTransform(std::array<std::array<double, 4>, 4> const& t, std::array<double, 3> &a)
{
	a[0] = atan(t[1][0] / t[0][0]);
	a[1] = asin(- t[2][0]);
	a[2] = atan(t[2][1] / t[2][2]);
	
	return 0;
}

int TaitBryanZYX::GetAngle(std::string const& s)
{
	if(strcmp(s.c_str(), "x") == 0)return 2;
	if(strcmp(s.c_str(), "y") == 0)return 1;
	if(strcmp(s.c_str(), "z") == 0)return 0;

	std::cout << s << std::endl;

	return -1;
}
