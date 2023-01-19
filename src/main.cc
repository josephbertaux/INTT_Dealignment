#include "index/IndexSetWrapper.h"
#include "align/AlignTransform.h"
#include "dtctr/InttSensorSurveyReader.h"

#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::string sensor_survey_dir = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey_data/";

	int layer = 3;
	int ladder = 4;
	int sensor = 0;
	int strip_z = 0;
	int strip_x = 0;
	double d = 0.0;
	char buff[16] = {"\0"};
	std::string s = "";

	AlignTransform t;	//nominal
	AlignTransform u;	//actual

	TVector3 a;
	TVector3 b;

	InttSensorSurveyReader sensor_reader;

	for(layer = 0; layer < INTT::LAYER; ++layer)
	{
		for(ladder = 0; ladder < INTT::LADDER[layer]; ++ladder)
		{
			sprintf(buff, "B%iL%03i.txt", layer / 2, (layer % 2) * 100 + ladder);
			s = sensor_survey_dir + buff;
			std::cout << buff << std::endl;

			if(sensor_reader.ReadSurveyFile(s))continue;

			for(sensor = 0; sensor < INTT::SENSOR; ++sensor)
			{
				d = 0.0;
				for(strip_x = 0; strip_x < INTT::STRIP_X; ++strip_x)
				{
					for(strip_z = 0; strip_z < INTT::STRIP_Z[sensor]; ++strip_z)
					{
						if(sensor_reader.GetNominalPixelToLadder(sensor, strip_x, strip_z, t))continue;
						if(sensor_reader.GetActualPixelToLadder(sensor, strip_x, strip_z, u))continue;

						a[0] = t.Pos(0);
						a[1] = t.Pos(1);
						a[2] = t.Pos(2);

						b[0] = u.Pos(0);
						b[1] = u.Pos(1);
						b[2] = u.Pos(2);

						a = a - b;
						if(a.Mag() > d)d = a.Mag();
					}
				}
				std::cout << "\t" << sensor << ":\t" << d << "\t (cm)" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	return 0;
}
