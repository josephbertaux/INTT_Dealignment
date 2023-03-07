#include "AlignTransform.h"

AlignTransform::AlignTransform()
{
	//Do nothing
}

AlignTransform::AlignTransform(const AlignTransform& o)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < 3; ++i)angs[i] = o.angs[i];
	for(i = 0; i < 4; ++i)for(j = 0; j < 4; ++j)axes[i][j] = o.axes[i][j];

	angle_convention = o.angle_convention;
}

AlignTransform operator*(AlignTransform& lhs, AlignTransform& rhs)
{
	int i = 0;
	int j = 0;
	int k = 0;

	AlignTransform t;

	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			t[i][j] = 0.0;
			for(k = 0; k < 4; ++k)t[i][j] += (lhs[i][k]) * (rhs[k][j]);
		}
	}

	return t;
}

std::array<double, 4>& AlignTransform::operator[](const int& i)
{
	return axes[i];
}

AlignTransform AlignTransform::Inverse()
{
	AlignTransform lhs = *this;
	AlignTransform rhs;

	int i = 0;
	int j = 0;
	int k = 0;

	double d = 0.0;

	for(j = 0; j < 4; ++j)
	{
		//find a pivot
		d = 0.0;
		for(i = j; i < 4; ++i)
		{
			if(std::abs(lhs[i][j]) > d)
			{
				d = std::abs(lhs[i][j]);
				k = i;
			}
		}

		//Check for singularity
		if(d < NUM_THRES)std::cout << "singular" << std::endl;

		//Pivot was found on row k; exchanges rows j and k to move it to diagonal
		for(i = 0; i < 4; ++i)
		{
			d = lhs[j][i];
			lhs[j][i] = lhs[k][i];
			lhs[k][i] = d;

			d = rhs[j][i];
			rhs[j][i] = rhs[k][i];
			rhs[k][i] = d;
		}

		//Normalize the pivot row
		d = 1.0 / lhs[j][j];
		for(i = 0; i < 4; ++i)
		{
			lhs[j][i] *= d;
			rhs[j][i] *= d;
		}

		//Upwards and downwards row elimination
		for(i = 0; i < 4; ++i)
		{
			if(i == j)continue;

			d = -lhs[i][j];

			for(k = 0; k < 4; ++k)
			{
				lhs[i][k] += d * lhs[j][k];
				rhs[i][k] += d * rhs[j][k];
			}
		}
	}

	return rhs;
}

double& AlignTransform::Pos(const int& i)
{
	return axes[i][3];
}

double& AlignTransform::Ang(const int& i)
{
	return angs[i];
}

double& AlignTransform::Ang(const std::string& s)
{
	return angs[angle_convention->GetAngle(s)];
}

int AlignTransform::Check()
{
	//return 1 on error
	int i;
	int j;
	int k;
	double d;

	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < i; ++j)
		{
			d = 0;
			for(k = 0; k < 3; ++k)
			{
				d += axes[k][j] * axes[k][i];
			}
			if(d < NUM_THRES)return 1;
		}
	}

	return 0;
}
int AlignTransform::Orthonormalize()
{
	int i;
	int j;
	int k;
	double d;

	for(i = 0; i < 3; ++i)
	{
		//Orthogonalize axis i to axes j < i
		//Assuming axis j is normalized
		for(j = 0; j < i; ++j)
		{
			d = 0;
			for(k = 0; k < 3; ++k)
			{
				d += axes[k][j] * axes[k][i];
			}
			for(k = 0; k < 3; ++k)
			{
				axes[k][i] -= d * axes[k][j];
			}
		}

		d = 0;
		for(k = 0; k < 3; ++k)
		{
			d += axes[k][i] * axes[k][i];
		}
		if(d < NUM_THRES)return 1; //linearly dependent
		d = sqrt(d);
		for(k = 0; k < 3; ++k)
		{
			axes[k][i] /= d;
		}
	}

	SetAnglesFromTransform();

	return 0;
}

int AlignTransform::SetAxis(const int& i, const std::array<double, 3>& a)
{
	if(!(0 <= i and i < 3))return 1;

	int j;
	int k;
	double d;

	//Assign the values to the column representing this axis
	//0 is 'x', 1 is 'y', 2 is 'z'
	d = 0;
	for(j = 0; j < 3; ++j)
	{
		axes[j][i] = a[j];
		d += a[j] * a[j];
	}

	//I'm leaving it on the user
	//to make an explicit call to orthonormalize
	//after explcitly setting multiple axes
	//to avoid truncation/rounding errors through
	//exessive Gauss-Jordan elimination and normalizations

	return 0;
}

int AlignTransform::SetTransformFromAngles()
{
	return angle_convention->SetTransformFromAngles(axes, angs);
}

int AlignTransform::SetAnglesFromTransform()
{
	return angle_convention->SetAnglesFromTransform(axes, angs);
}

void AlignTransform::Reset()
{
	int i = 0;
	int j = 0;

	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < i; ++j)
		{
			axes[i][j] = 0.0;
		}
		axes[i][i] = 1.0;
		for(j = i + 1; j < 4; ++j)
		{
			axes[i][j] = 0.0;
		}
	}

	for(i = 0; i < 3; ++i)
	{
		angs[i] = 0.0;
	}

}

void AlignTransform::PrintRow(const int& i, std::string s)
{
	int j = 0;
	while(true)
	{
		printf(s.c_str(), axes[i][j]);

		if(++j >= 4)break;

		printf("\t");
	}
}

void AlignTransform::Print(std::string s)
{
	int i = 0;
	while(true)
	{
		PrintRow(i, s);
		printf("\n");

		if(++i >= 4)break;
	}
}
