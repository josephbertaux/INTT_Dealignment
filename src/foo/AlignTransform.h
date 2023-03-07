#ifndef ALIGN_TRANSFORM_H
#define ALIGN_TRANSFORM_H

#include "AngleConvention.h"
#include "TaitBryanZYX.h"

#include <cstdlib>
#include <array>
#include <memory>
#include <type_traits>

#include <string>
#include <iostream>

class AlignTransform
{
private:
	static constexpr double NUM_THRES = 1.0e-16;
	std::shared_ptr<AngleConvention> angle_convention = std::static_pointer_cast<AngleConvention>(std::make_shared<TaitBryanZYX>());
	std::array<std::array<double, 4>, 4> axes = {{{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}}};
	//std::array<std::array<double, 4>, 4> axes = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};
	std::array<double, 3> angs = {0.0, 0.0, 0.0};

public:
	AlignTransform();
	AlignTransform(const AlignTransform&);

	friend AlignTransform operator*(AlignTransform&, AlignTransform&);
	std::array<double, 4>& operator[](const int&);

	AlignTransform Inverse();

	double& Pos(const int&);
	double& Ang(const int&);
	double& Ang(const std::string&);

	int Check();
	int Orthonormalize();
	int SetAxis(const int&, const std::array<double, 3>&);
	int SetTransformFromAngles();
	int SetAnglesFromTransform();

	void Reset();

	void PrintRow(const int&, std::string= "%+10.4f");
	void Print(std::string = "%+10.4f");

	template <typename T>
	int SetConvention()
	{
		if(!(std::is_base_of<AngleConvention, T>::value))return 1;

		angle_convention = std::static_pointer_cast<AngleConvention>(std::make_shared<T>());

		return 0;
	}
};

#endif
