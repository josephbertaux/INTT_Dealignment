#ifndef LADDER_READER_H
#define LADDER_READER_H

#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "AlignTransform.h"

class LadderReader
{
	static const std::string path;
	typedef std::map<std::string, std::array<double, 3>> CORNER_MAP;
	typedef std::map<std::string, std::tuple<CORNER_MAP, CORNER_MAP, bool>> LADDER_MAP;
	LADDER_MAP marks;
	std::map<int, std::string> indexes;

	//helper methods
	AlignTransform GetTransformToWorld(std::array<std::array<double, 3>, 4> const&);
	AlignTransform GetTransformToWorld(CORNER_MAP const&);

public:
	LadderReader();

	int SetMarksFromFile(std::string const&);

	AlignTransform GetNominalTransformToWorld(int const&);	//really just a helper, might make private
	AlignTransform GetActualTransformToWorld(int const&);	//really just a helper, might make private

	AlignTransform GetNominalSensorToLadder(int const&);	//important
	AlignTransform GetActualSensorToLadder(int const&);	//important

	AlignTransform GetNominalMarkInWorld(int const&, int const&);	//really just a helper, might make private
	AlignTransform GetActualMarkInWorld(int const&, int const&);	//really just a helper, might make private

	AlignTransform GetNominalMarkInLadder(int const&, int const&);	//important
	AlignTransform GetActualMarkInLadder(int const&, int const&);	//important

	void Print(std::string const& = "%10.6f");
};

#endif
