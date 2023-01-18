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
	char buff[16] = {"\0"};
	std::string s = "";

	AlignTransform t;
	InttSensorSurveyReader sensor_reader;

	for(layer = 0; layer < INTT::LAYER; ++layer)
	{
		for(ladder = 0; ladder < INTT::LADDER[layer]; ++ladder)
		{
			sprintf(buff, "B%iL%03i.txt", layer / 2, (layer % 2) * 100 + ladder);
			s = sensor_survey_dir + buff;
			if(sensor_reader.ReadSurveyFile(s))continue;

			std::cout << buff << std::endl;
			for(sensor = 0; sensor < INTT::SENSOR; ++sensor)
			{
				sensor_reader.GetActualSensorTransform(sensor, t);
				t.Print();
				std::cout << std::endl;
			}
		}
	}

	return 0;
}
