#include "BarrelReader.h"

const std::string BarrelReader::path = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey_data/";

BarrelReader::BarrelReader()
{
	marks["foo"] =
	{//tuple
		{//nominal map
			{"bar", {0.0, 0.0, 0.0}},
			{"biz", {0.0, 0.0, 0.0}}
		},
		{//actual map
			{"bar", {0.0, 0.0, 0.0}},
			{"biz", {0.0, 0.0, 0.0}}
		},
		false	
	};

	indexes[-1] = "foo";
}

int BarrelReader::SetMarksFromFile(std::string const& barrel_str)
{
	int return_val = 0;
	std::stringstream output_str;
	output_str << "int LadderReader::SetMarksFromFile(std::string const& ladder_str)";

	bool b;
	int i;
	int j;
	float f[2];
	std::string line;
	BARREL_MAP::iterator itr;
	CORNER_MAP::iterator jtr;
	std::ifstream survey_file;

	if(barrel_str.empty())
	{
		output_str << "\tArgument \"barrel_str\" is empty string" << std::endl;
		return_val = 1;
		goto label;
	}

	survey_file.open((path + barrel_str), std::ifstream::in);
	if(!survey_file.good())
	{
		output_str << "\tCould not open a good ifstream with path:" << std::endl;
		output_str << "\t" << path << barrel_str << std::endl;
		return_val = 1;
		goto label;
	}

	//See if the current line contains a substring
	//That indicates it denotes a set of marks
	for(itr = marks.begin(); itr != marks.end(); ++itr)
	{
		std::get<2>(itr->second) = b;
	}

	for(line; std::getline(survey_file, line);)
	{
		//See if the current line contains a substring
		//That indicates it denotes a set of marks
		for(itr = marks.begin(); itr != marks.end(); ++itr)
		{
			if(line.find(itr->first) != std::string::npos)break;
		}
		if(itr == marks.end())continue;

		//It denotes a set of marks
		//See which mark it corresponds to(r(jtr = std::get<1>(itr->second).begin(); jtr != std::get<1>(itr->second).end(); ++jtr)
		{
			if(line.find(jtr->first) != std::string::npos)break;
		}

		if(jtr == std::get<1>(itr->second).end())continue;

		//the line corresponds to some corner of some set of marks
		//get the next 3 lines to determine the coordinates of that mark
		b = true;
		for(i = 0; i < 3; ++i)
		{
			std::getline(survey_file, line);
			j = sscanf(line.c_str(), "%*s %*s %*s %f %f", &(f[0]), &(f[1]));
			if(j)(jtr->second)[i] = f[j - 1];
			else b = false;
		}
		std::get<2>(itr->second) = b;
	}

	//run through the map again
	//restor the marks to nominal if the flag is set to false
	for(itr = marks.begin(); itr != marks.end(); ++itr)
	{
		//skip marks that were successfully read
		if(std::get<2>(itr->second))continue;

		for(jtr = std::get<1>(itr->second).begin(); jtr != std::get<1>(itr->second).end(); ++jtr)
		{
			for(i = 0; i < 3; ++i)
			{
				(jtr->second)[i] = (std::get<0>(itr->second)[jtr->first])[i];
			}
		}
	}

	label:
	if(survey_file.is_open())survey_file.close();
	output_str << std::ends;
	if(return_val)std::cout << output_str.str() << std::endl;
	return return_val;
}

AlignTransform BarrelReader::GetNominalTransformToWorld(int const& i, int const& j)
{
	AlignTransform a;
	AlignTransform b;
	double r = 0.0;
	double t = 8.0 * atan(1.0); //2 pi
	double d = 8.0 * atan(1.0); //2 pi

	switch(i)
	{
		case 0:
			r = 71.87489;
			d /= 12.0;
			t += d / 2.0;
			break;
		case 1:
			r = 77.99527;
			d /= 12.0;
			break;
		case 2:
			r = 98.80091;
			d /= 16.0;
			t += d / 2.0;
			break;
		case 3:
			r = 103.28663;
			d /= 16.0;
			break;
	}

	t += j * d;

	a.Pos(0) = r;
	a.Ang("z") = -2.0 * atan(1.0); //right angle
	a.SetTransformFromAngles();

	b.Ang("z") = t;
	b.SetTransformFromAngles();

	a = b * a;

	return a;
}
