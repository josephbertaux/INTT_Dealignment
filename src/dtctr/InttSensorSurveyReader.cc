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
