#include "LadderReader.h"

const std::string LadderReader::path = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey_data/";

LadderReader::LadderReader()
{
	//Ladder itself
	marks["Endcap"] =
	{//tuple<map, map, bool>
		{//first map (nominal, string identifies to mark position)
			{"Hole 1",	{0.0,	0.0,	0.0}},
			{"Hole 2",	{492.0,	0.0,	0.0}},
			{"Hole 3",	{492.0,	34.0,	0.0}},
			{"Hole 4",	{0.0,	34.0,	0.0}}
		},

		{//second map (actual, string identifies to mark position)
			{"Hole 1",	{0.0,	0.0,	0.0}},
			{"Hole 2",	{492.0,	0.0,	0.0}},
			{"Hole 3",	{492.0,	34.0,	0.0}},
			{"Hole 4",	{0.0,	34.0,	0.0}}
		},

		//whether the actual mark was successfully read
		false
	};

	//Sensor A
	marks["Sensor A"] = 
	{//tuple<map, map, bool>
		{//first map (nominal, string identifies to mark position)
			{"Cross 1",	{13.5,	6.0,	0.0}},
			{"Cross 2",	{115.0,	6.0,	0.0}},
			{"Cross 3",	{115.0,	28.0,	0.0}},
			{"Cross 4",	{13.5,	28.0,	0.0}}
		},

		{//second map (actual, string identifies to mark position)
			{"Cross 1",	{13.5,	6.0,	0.0}},
			{"Cross 2",	{115.0,	6.0,	0.0}},
			{"Cross 3",	{115.0,	28.0,	0.0}},
			{"Cross 4",	{13.5,	28.0,	0.0}}
		},

		//whether the actual mark was successfully read
		false
	};

	//Sensor B
	marks["Sensor B"] =
	{//tuple<map, map, bool>
		{//first map (nominal, string identifies to mark position)
			{"Cross 1",	{115.7,	6.0,	0.0}},
			{"Cross 2",	{245.2,	6.0,	0.0}},
			{"Cross 3",	{245.2,	28.0,	0.0}},
			{"Cross 4",	{115.7,	28.0,	0.0}}
		},

		{//second map (actual, string identifies to mark position)
			{"Cross 1",	{115.7,	6.0,	0.0}},
			{"Cross 2",	{245.2,	6.0,	0.0}},
			{"Cross 3",	{245.2,	28.0,	0.0}},
			{"Cross 4",	{115.7,	28.0,	0.0}}
		},

		//whether the actual mark was successfully read
		false
	};
	

	//Sensor C
	marks["Sensor C"] =
	{//tuple<map, map, bool>
		{//first map (nominal, string identifies to mark position)
			{"Cross 1",	{246.8,	6.0,	0.0}},
			{"Cross 2",	{376.3,	6.0,	0.0}},
			{"Cross 3",	{376.3,	28.0,	0.0}},
			{"Cross 4",	{246.8,	28.0,	0.0}}
		},

		{//second map (actual, string identifies to mark position)
			{"Cross 1",	{246.8,	6.0,	0.0}},
			{"Cross 2",	{376.3,	6.0,	0.0}},
			{"Cross 3",	{376.3,	28.0,	0.0}},
			{"Cross 4",	{246.8,	28.0,	0.0}}
		},

		//whether the actual mark was successfully read
		false
	};
	

	//Sensor D
	marks["Sensor D"] =
	{//tuple<map, map, bool>
		{//first map (nominal, string identifies to mark position)
			{"Cross 1",	{377.0,	6.0,	0.0}},
			{"Cross 2",	{478.5,	6.0,	0.0}},
			{"Cross 3",	{478.5,	28.0,	0.0}},
			{"Cross 4",	{377.0,	28.0,	0.0}}
		},

		{//second map (actual, string identifies to mark position)
			{"Cross 1",	{377.0,	6.0,	0.0}},
			{"Cross 2",	{478.5,	6.0,	0.0}},
			{"Cross 3",	{478.5,	28.0,	0.0}},
			{"Cross 4",	{377.0,	28.0,	0.0}}
		},

		//whether the actual mark was successfully read
		false
	};

	indexes[-1] = "Endcap";
	indexes[1] = "Sensor A";
	indexes[0] = "Sensor B";
	indexes[2] = "Sensor C";
	indexes[3] = "Sensor D";
}

int LadderReader::SetMarksFromFile(std::string const& ladder_str)
{
	int return_val = 0;
	std::stringstream output_str;
	output_str << "int LadderReader::SetMarksFromFile(std::string const& ladder_str)";

	bool b;
	int i;
	int j;
	float f[2];
	std::string line;
	LADDER_MAP::iterator itr;
	CORNER_MAP::iterator jtr;
	std::ifstream survey_file;

	//run through the map and set the flag for each mark
	//that it wasn't gotten successfully
	//and restore the "actual" displacements to nominal
	for(itr = marks.begin(); itr != marks.end(); ++itr)
	{
		std::get<2>(itr->second) = b;
		for(jtr = std::get<1>(itr->second).begin(); jtr != std::get<1>(itr->second).end(); ++jtr)
		{
			for(i = 0; i < 3; ++i)
			{
				(jtr->second)[i] = (std::get<0>(itr->second)[jtr->first])[i];
			}	
		}
	}

	if(ladder_str.empty())
	{
		output_str << "\tArgument \"ladder_str\" is empty string" << std::endl;
		return_val = 1;
		goto label;
	}

	survey_file.open((path + ladder_str), std::ifstream::in);
	if(!survey_file.good())
	{
		output_str << "\tCould not open a good ifstream with path:" << std::endl;
		output_str << "\t" << path << ladder_str << std::endl;
		return_val = 1;
		goto label;
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
		//See which mark it corresponds to
		for(jtr = std::get<1>(itr->second).begin(); jtr != std::get<1>(itr->second).end(); ++jtr)
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
	//restore the marks to nominal if the flag is set to false
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

AlignTransform LadderReader::GetTransformToWorld(std::array<std::array<double, 3>, 4> const& c)
{
	AlignTransform a;

	int i;
	int j;
	std::array<double, 3> t;

	//	Corners are arranged as:
	//	    x
	//	    ^
	//	    |
	//	+-------+
	//	|3     2|
	//	|   y   |--->z
	//	|0     1|
	//	+-------+

	//z axis should be sum of diangles from 0->2 and 3->1
	for(i = 0; i < 3; ++i)t[i] = (c[2][i] - c[0][i]) + (c[1][i] - c[3][i]);
	a.SetAxis(2, t);

	//x axis should be sum of diangles from 0->2 and 3->1
	for(i = 0; i < 3; ++i)t[i] = (c[2][i] - c[0][i]) + (c[3][i] - c[1][i]);
	a.SetAxis(0, t);

	//y axis should be z cross x
	a.SetAxis
	(1,
		{
		//	y_x =
		//	z_y     * x_z     - z_z     * x_y
			a[1][2] * a[2][0] - a[2][2] * a[1][0],
		//	y_y =
		//	z_z     * x_x     - z_x     * x_z
			a[2][2] * a[0][0] - a[0][2] * a[2][0],
		//	y_z =
		//	z_x     * x_y     - z_y     * x_x
			a[0][2] * a[1][0] - a[1][2] * a[0][0]
		}
	);
	a.Orthonormalize();
	a.SetAnglesFromTransform();

	//Center or offset should be average of the corners
	for(i = 0; i < 3; ++i)
	{
		t[i] = 0.0;
		for(j = 0; j < 4; ++j)
		{
			t[i] += c[j][i];
		}
		t[i] *= 0.25;
		a.Pos(i) = t[i];
	}

	return a;
}

AlignTransform LadderReader::GetTransformToWorld(CORNER_MAP const &m)
{
	int i;
	int j;
	std::array<std::array<double, 3>, 4> c;
	CORNER_MAP::const_iterator itr;
	for(i = 0; i < 4; ++i)
	{
		for(itr = m.begin(); itr != m.end(); ++itr)
		{
			if((itr->first).find(std::to_string(i + 1)) != std::string::npos)break;
		}

		if(itr == m.end())continue;//should really through error or return with error flag

		for(j = 0; j < 3; ++j)
		{
			c[i][j] = (itr->second)[j];
		}
	}
	return GetTransformToWorld(c);
}

AlignTransform LadderReader::GetNominalTransformToWorld(int const& i)
{
	return GetTransformToWorld(std::get<0>(marks[indexes[i]]));
}

AlignTransform LadderReader::GetActualTransformToWorld(int const& i)
{
	return GetTransformToWorld(std::get<1>(marks[indexes[i]]));
}

AlignTransform LadderReader::GetNominalSensorToLadder(int const& i)
{
	AlignTransform a = GetNominalTransformToWorld(i);	//Sensor
	AlignTransform b = GetNominalTransformToWorld(-1);	//Ladder

	b = b.Inverse();
	a = b * a;

	return a;
}

AlignTransform LadderReader::GetActualSensorToLadder(int const& i)
{
	AlignTransform a = GetActualTransformToWorld(i);	//Sensor
	AlignTransform b = GetActualTransformToWorld(-1);	//Ladder

	b = b.Inverse();
	a = b * a;

	return a;
}

AlignTransform LadderReader::GetNominalMarkInWorld(int const& index, int const& corner)
{
	int i;
	AlignTransform a;
	CORNER_MAP::const_iterator itr;

	for(itr = std::get<0>(marks[indexes[index]]).begin(); itr != std::get<0>(marks[indexes[index]]).end(); ++itr)
	{
		if(itr->first.find(std::to_string(corner + 1)) != std::string::npos)break;
	}

	for(i = 0; i < 3; ++i)
	{
		a.Pos(i) = (itr->second)[i];
	}

	return a;
}

AlignTransform LadderReader::GetActualMarkInWorld(int const& index, int const& corner)
{
	int i;
	AlignTransform a;
	CORNER_MAP::const_iterator itr;

	for(itr = std::get<1>(marks[indexes[index]]).begin(); itr != std::get<1>(marks[indexes[index]]).end(); ++itr)
	{
		if(itr->first.find(std::to_string(corner + 1)) != std::string::npos)break;
	}

	for(i = 0; i < 3; ++i)
	{
		a.Pos(i) = (itr->second)[i];
	}

	return a;
}

AlignTransform LadderReader::GetNominalMarkInLadder(int const& index, int const& corner)
{
	AlignTransform a = GetNominalMarkInWorld(index, corner); //The mark's transform in world coordinates
	AlignTransform b = GetNominalTransformToWorld(-1); //The transform from ladder coordinates to world coordinates

	b = b.Inverse();
	a = b * a;
	return a;
}

AlignTransform LadderReader::GetActualMarkInLadder(int const& index, int const& corner)
{
	AlignTransform a = GetActualMarkInWorld(index, corner); //The mark's transform in world coordinates
	AlignTransform b = GetActualTransformToWorld(-1); //The transform from ladder coordinates to world coordinates

	b = b.Inverse();
	a = b * a;
	return a;
}

void LadderReader::Print(std::string const& f)
{
	//Print the marks
	int i;
	LADDER_MAP::const_iterator itr;
	CORNER_MAP::const_iterator jtr;

	for(itr = marks.begin(); itr != marks.end(); ++itr)
	{
		std::cout << itr->first << std::endl;
		std::cout << "\tNominals:\t   x\t\t   y\t\t   z\t(mm)" << std::endl;
		for(jtr = std::get<0>(itr->second).begin(); jtr != std::get<0>(itr->second).end(); ++jtr)
		{
			std::cout << "\t\t" << jtr->first;
			for(i = 0; i < 3; ++i)
			{
				std::cout << "\t";
				printf(f.c_str(), (jtr->second)[i]);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "\tActuals:\t   x\t\t   y\t\t   z\t(mm)" << std::endl;
		for(jtr = std::get<1>(itr->second).begin(); jtr != std::get<1>(itr->second).end(); ++jtr)
		{
			std::cout << "\t\t" << jtr->first;
			for(i = 0; i < 3; ++i)
			{
				std::cout << "\t";
				printf(f.c_str(), (jtr->second)[i]);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "\tRead Success: " << std::get<2>(itr->second) << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
