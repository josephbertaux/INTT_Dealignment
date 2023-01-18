#include "InttSensorSurveyReader.h"

InttSensorSurveyReader::InttSensorSurveyReader()
{
	for(int i = 0; i < 4; ++i)
	{
		nominal_crosses.push_back(TVector3());
		actual_crosses.push_back(TVector3());

		nominal_endcaps.push_back(TVector3());
		actual_endcaps.push_back(TVector3());
	}

	crosses["Cross 1"]=		{&(nominal_crosses[0]), &(actual_crosses[0])};
	crosses["Cross 2"]=		{&(nominal_crosses[1]), &(actual_crosses[1])};
	crosses["Cross 3"]=		{&(nominal_crosses[2]), &(actual_crosses[2])};
	crosses["Cross 4"]=		{&(nominal_crosses[3]), &(actual_crosses[3])};

	endcaps["Endcap Hole 1"]=	{&(nominal_endcaps[0]), &(actual_endcaps[0])};
	endcaps["Endcap Hole 2"]=	{&(nominal_endcaps[1]), &(actual_endcaps[1])};
	endcaps["Endcap Hole 3"]=	{&(nominal_endcaps[2]), &(actual_endcaps[2])};
	endcaps["Endcap Hole 4"]=	{&(nominal_endcaps[3]), &(actual_endcaps[3])};

	marks["Sensor A - Cross 1"]=	{TVector3	(13.5,	6.0,	0.0),	TVector3(), false};
	marks["Sensor A - Cross 2"]=	{TVector3	(115.0,	6.0,	0.0),	TVector3(), false};
	marks["Sensor A - Cross 3"]=	{TVector3	(115.0,	28.0,	0.0),	TVector3(), false};
	marks["Sensor A - Cross 4"]=	{TVector3	(13.5,	28.0,	0.0),	TVector3(), false};

	marks["Sensor B - Cross 1"]=	{TVector3	(115.7,	6.0,	0.0),	TVector3(), false};
	marks["Sensor B - Cross 2"]=	{TVector3	(245.2,	6.0,	0.0),	TVector3(), false};
	marks["Sensor B - Cross 3"]=	{TVector3	(245.2,	28.0,	0.0),	TVector3(), false};
	marks["Sensor B - Cross 4"]=	{TVector3	(115.7,	28.0,	0.0),	TVector3(), false};

	marks["Sensor C - Cross 1"]=	{TVector3	(246.8,	6.0,	0.0),	TVector3(), false};
	marks["Sensor C - Cross 2"]=	{TVector3	(376.3,	6.0,	0.0),	TVector3(), false};
	marks["Sensor C - Cross 3"]=	{TVector3	(376.3,	28.0,	0.0),	TVector3(), false};
	marks["Sensor C - Cross 4"]=	{TVector3	(246.8,	28.0,	0.0),	TVector3(), false};

	marks["Sensor D - Cross 1"]=	{TVector3	(377.0,	6.0,	0.0),	TVector3(), false};
	marks["Sensor D - Cross 2"]=	{TVector3	(478.5,	6.0,	0.0),	TVector3(), false};
	marks["Sensor D - Cross 3"]=	{TVector3	(478.5,	28.0,	0.0),	TVector3(), false};
	marks["Sensor D - Cross 4"]=	{TVector3	(377.0,	28.0,	0.0),	TVector3(), false};

	marks["Endcap Hole 1"]=		{TVector3	(0.0,	0.0,	0.0),	TVector3(), false};
	marks["Endcap Hole 2"]=		{TVector3	(492.0,	0.0,	0.0),	TVector3(), false};
	marks["Endcap Hole 3"]=		{TVector3	(492.0,	34.0,	0.0),	TVector3(), false};
	marks["Endcap Hole 4"]=		{TVector3	(0.0,	34.0,	0.0),	TVector3(), false};
}

int InttSensorSurveyReader::ReadSurveyFile(const std::string& filename)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::ReadSurveyFile(const std::string& filename)" << std::endl;

	int i = 0;
	float f[2] = {0.0, 0.0};

	std::string line;
	std::ifstream survey_file;
	std::map<std::string, std::tuple<TVector3, TVector3, bool>>::iterator itr = marks.begin();

	if(filename == "")
	{
		out << "\tPassed argument \"filename\" is empty string" << std::endl;
		return_val = 1;
		goto label;
	}
	survey_file.open(filename.c_str(), std::ifstream::in);
	if(!survey_file.good())
	{
		out << "\tCould not produce good std::ifstream from path:" << std::endl;
		out << "\t\t" << filename << std::endl;
		return_val = 1;
		goto label;
	}

	for(line; std::getline(survey_file, line);)
	{
		for(itr = marks.begin(); itr != marks.end(); ++itr)
		{
			if(line.find(itr->first) != std::string::npos)
			{
				std::getline(survey_file, line);
				i = sscanf(line.c_str(), "%*s %*s %*s %f %f", &(f[0]), &(f[1]));
				if(i)
				{
						std::get<1>(itr->second).SetX(f[i - 1]);
						std::get<2>(itr->second) = true;
				}
				else
				{
						out << "\tBad read for coordinate:" << std::endl;
						out << "\t\t" << itr->first << "\tX" << std::endl;
						return_val = 1;
				}

				std::getline(survey_file, line);
				i = sscanf(line.c_str(), "%*s %*s %*s %f %f", &(f[0]), &(f[1]));
				if(i)
				{
						std::get<1>(itr->second).SetY(f[i - 1]);
						std::get<2>(itr->second) = true;
				}
				else
				{
						out << "\tBad read for coordinate:" << std::endl;
						out << "\t\t" << itr->first << "\tY" << std::endl;
						return_val = 1;
				}

				std::getline(survey_file, line);
				i = sscanf(line.c_str(), "%*s %*s %*s %f %f", &(f[0]), &(f[1]));
				if(i)
				{
						std::get<1>(itr->second).SetZ(f[i - 1]);
						std::get<2>(itr->second) = true;
				}
				else
				{
						out << "\tBad read for coordinate:" << std::endl;
						out << "\t\t" << itr->first << "\tZ" << std::endl;
						return_val = 1;
				}
				

				break;
			}
		}
	}

	label:
	if(survey_file.is_open())survey_file.close();

	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}

int InttSensorSurveyReader::SetMarks(const int& i)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::ComputeTransform(const int& i, AlignTransform& t)" << std::endl;

	std::string s = "";

	std::map<std::string, std::tuple<TVector3, TVector3, bool>>::const_iterator mark = marks.begin();
	std::map<std::string, std::pair<TVector3*, TVector3*>>::const_iterator crosses_itr = crosses.begin();
	std::map<std::string, std::pair<TVector3*, TVector3*>>::const_iterator endcaps_itr = endcaps.begin();

	if(!(0 <= i && i < INTT::SENSOR))
	{
		out << "\tPassed argument i (" << i << ") out valid range [0, 4)" << std::endl;
		return_val = 1;
		goto label;
	}

	for(crosses_itr = crosses.begin(); crosses_itr != crosses.end(); ++crosses_itr)
	{
		s = sensors[i] + " - " + crosses_itr->first;
		mark = marks.find(s);
		if(mark == marks.end())
		{
			out << "\tNo item with key \"" << s << "\" found in marks map (typo in source code?)" << std::endl;
			return_val = 1;
			goto label;
		}
		if(!std::get<2>(mark->second))
		{
			out << "\tMark \"" << s << "\" was not set" << std::endl;
			out << "\tWas this preceded by a successful call to ReadSurveyFile in the main program?" << std::endl;
			return_val = 1;
			goto label;
		}

		*((crosses_itr->second).first) = std::get<0>(mark->second);
		*((crosses_itr->second).second) = std::get<1>(mark->second);
	}

	for(endcaps_itr = endcaps.begin(); endcaps_itr != endcaps.end(); ++endcaps_itr)
	{
		s = endcaps_itr->first;
		mark = marks.find(s);
		if(mark == marks.end())
		{
			out << "\tNo item with key \"" << s << "\" found in marks map (typo in source code?)" << std::endl;
			return_val = 1;
			goto label;
		}
		if(!std::get<2>(mark->second))
		{
			out << "\tMark \"" << s << "\" was not set" << std::endl;
			out << "\tWas this preceded by a successful call to ReadSurveyFile in the main program?" << std::endl;
			return_val = 1;
			goto label;
		}

		*((endcaps_itr->second).first) = std::get<0>(mark->second);
		*((endcaps_itr->second).second) = std::get<1>(mark->second);
	}

	label:
	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}

int InttSensorSurveyReader::GetTransformFromMarks(AlignTransform& t, const std::vector<TVector3>& transform_marks)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::GetTransformFromMarks(AlignTransform& t, const std::vector<TVector3>& transform_marks)" << std::endl;
	//local to world

	int i = 0;
	int j = 0;
	TVector3 axes[3];

	axes[2] = (transform_marks[2] - transform_marks[0]) - (transform_marks[3] - transform_marks[1]);
	axes[0] = (transform_marks[2] - transform_marks[0]) + (transform_marks[3] - transform_marks[1]);
	axes[1] = axes[2].Cross(axes[0]);

	axes[0] = axes[0].Unit();
	axes[1] = axes[1].Unit();
	axes[2] = axes[2].Unit();

	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			t[i][j] = axes[j][i];
		}

		t.Pos(i) = (transform_marks[0][i] + transform_marks[1][i] + transform_marks[2][i] + transform_marks[3][i]) / 4.0;
	}
	t.SetAnglesFromTransform();

	label:
	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}

int InttSensorSurveyReader::GetTransform(AlignTransform& t, const std::vector<TVector3>& child_marks, const std::vector<TVector3>& parent_marks)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::GetTransform(AlignTransform& t, const std::vector<TVector3>& child_marks, const std::vector<TVector3>& parent_marks)" << std::endl;
	//child to parent

	AlignTransform parent;	//parent to world
	AlignTransform child;	//child to world

	if(GetTransformFromMarks(parent, parent_marks))
	{
		return_val = 1;
		goto label;
	}

	if(GetTransformFromMarks(child, child_marks))
	{
		return_val = 1;
		goto label;
	}

	parent = parent.Inverse();
	t = parent * child;

	label:
	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}

int InttSensorSurveyReader::GetNominalSensorTransform(const int& i, AlignTransform& t)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::GetNominalSensorTransform(const int& i, AlignTransform& t)" << std::endl;
	//nominal sensor to ladder

	if(SetMarks(i))
	{
		return_val = 1;
		goto label;
	}

	if(GetTransform(t, nominal_crosses, nominal_endcaps))
	{
		return_val = 1;
		goto label;
	}

	label:
	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}

int InttSensorSurveyReader::GetActualSensorTransform(const int& i, AlignTransform& t)
{
	int return_val = 0;
	std::stringstream out;
	out << "InttSensorSurveyReader::GetActualSensorTransform(const int& i, AlignTransform& t)" << std::endl;
	//actual sensor to ladder

	if(SetMarks(i))
	{
		return_val = 1;
		goto label;
	}

	if(GetTransform(t, actual_crosses, actual_endcaps))
	{
		return_val = 1;
		goto label;
	}

	label:
	out << std::ends;
	if(return_val)std::cout << out.str() << std::endl;
	return return_val;
}


void InttSensorSurveyReader::PrintMarks()
{
	std::map<std::string, std::tuple<TVector3, TVector3, bool>>::const_iterator itr;

	for(itr = marks.begin(); itr != marks.end(); ++itr)
	{
		std::cout << itr->first << std::endl;
		std::cout << "\tX:\t" << std::get<1>(itr->second).X() << "\t(" << std::get<0>(itr->second).X() << ")" << std::endl;
		std::cout << "\tY:\t" << std::get<1>(itr->second).Y() << "\t(" << std::get<0>(itr->second).Y() << ")" << std::endl;
		std::cout << "\tZ:\t" << std::get<1>(itr->second).Z() << "\t(" << std::get<0>(itr->second).Z() << ")" << std::endl;
	}
}
