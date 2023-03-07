#include "AlignTransform.h"
#include "LadderReader.h"
#include "BarrelReader.h"

int main()
{
	AlignTransform a;
	AlignTransform b;
	AlignTransform c;
	//LadderReader lr;

	//lr.SetMarksFromFile("B0L000.txt");
	//lr.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;

	//a = lr.GetNominalMarkInLadder(-1, 0);
	//a.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;

	//a = lr.GetActualMarkInLadder(3, 2);
	//a.Print();

	BarrelReader br;

	a = br.GetNominalTransformToWorld(0, 0);
	a.Print();

	std::cout << std::endl;
	std::cout << std::endl;

	a = br.GetNominalTransformToWorld(0, 1);
	a.Print();

	std::cout << std::endl;
	std::cout << std::endl;

	a = br.GetNominalTransformToWorld(0, 2);
	a.Print();

	std::cout << std::endl;
	std::cout << std::endl;

	a = br.GetNominalTransformToWorld(0, 3);
	a.Print();

	////==================================//
	//a = lr.GetNominalTransformToWorld(-1);
	//a.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;

	//b = a.Inverse();
	//c = a * b;
	//c.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;

	////==================================//
	//a = lr.GetActualTransformToWorld(-1);
	//a.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;

	//b = a.Inverse();
	//c = a * b;
	//c.Print();

	//std::cout << std::endl;
	//std::cout << std::endl;




	return 0;
}
