#ifndef INTT_SENSOR_SURVEY_READER_H
#define INTT_SENSOR_SURVEY_READER_H

#include "InttParameters.h"
#include "../align/AlignTransform.h"

#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>


class InttSensorSurveyReader
{
protected:
	std::vector<std::string> sensors = {"Sensor A", "Sensor B", "Sensor C", "Sensor D"};

	std::vector<TVector3> nominal_crosses;
	std::vector<TVector3> actual_crosses;

	std::vector<TVector3> nominal_endcaps;
	std::vector<TVector3> actual_endcaps;

	std::map<std::string, std::pair<TVector3*, TVector3*>> crosses;
	std::map<std::string, std::pair<TVector3*, TVector3*>> endcaps;

	std::map<std::string, std::tuple<TVector3, TVector3, bool>> marks;

public:
	std::string text_output_filename = "sensor_survey_data.root";
	std::string root_output_filename = "sensor_survey_read.out";

	//int ReadSurveyFile(const std::string&, std::stringstream&);
	//int ComputeRelativeTransform(const std::string&, TransformAlign);

	InttSensorSurveyReader();
};

#endif
