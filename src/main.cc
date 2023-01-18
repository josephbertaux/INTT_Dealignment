#include "index/IndexSetWrapper.h"
#include "align/AlignTransform.h"
#include "dtctr/InttSensorSurveyReader.h"

#include <string>
#include <vector>
#include <iostream>

int main()
{
	InttSensorSurveyReader sensor_reader;

	if(sensor_reader.ReadSurveyFile("/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey_data/B1L104.txt"))return 1;


	AlignTransform t;

	for(int i = 0; i < 4; ++i)
	{
		sensor_reader.GetNominalSensorTransform(i, t);
		t.Print();
		std::cout << std::endl;
	}

	return 0;
}
